#include "laser.h"
#include "meshes.h"

static LaserSystem laserSystem = {0};

LaserSystem* laser_system_create(void)
{
    laserSystem.mesh = mesh_create_laser_cube();
    laserSystem.matrices = malloc_uncached(sizeof(T3DMat4FP) * MAX_LASERS * FB_COUNT);
    laserSystem.cooldown = 0;

    for (int i = 0; i < MAX_LASERS; i++) {
        laserSystem.lasers[i].active = false;
    }

    return &laserSystem;
}

bool laser_fire(LaserSystem *system, float rotX, float rotY, AudioState *audio)
{
    if (system->cooldown > 0) {
        return false;
    }

    // Find inactive laser slot
    for (int i = 0; i < MAX_LASERS; i++) {
        if (!system->lasers[i].active) {
            // Build rotation matrix to get forward direction
            T3DMat4 rotMat;
            t3d_mat4_from_srt_euler(&rotMat,
                (float[3]){1.0f, 1.0f, 1.0f},
                (float[3]){rotX, rotY, 0.0f},
                (float[3]){0.0f, 0.0f, 0.0f}
            );

            // Transform forward vector (0,0,1) by rotation
            T3DVec3 forward = {{0, 0, 1}};
            T3DVec4 dir4;
            t3d_mat4_mul_vec3(&dir4, &rotMat, &forward);
            system->lasers[i].dir = (T3DVec3){{dir4.v[0], dir4.v[1], dir4.v[2]}};
            t3d_vec3_norm(&system->lasers[i].dir);

            // Start at cube's front face
            system->lasers[i].pos = (T3DVec3){{
                system->lasers[i].dir.v[0] * LASER_SPAWN_DISTANCE,
                system->lasers[i].dir.v[1] * LASER_SPAWN_DISTANCE,
                system->lasers[i].dir.v[2] * LASER_SPAWN_DISTANCE
            }};
            system->lasers[i].active = true;
            system->lasers[i].timer = LASER_LIFETIME;
            system->cooldown = LASER_COOLDOWN_FRAMES;

            audio_play_laser(audio);
            return true;
        }
    }

    return false;
}

void laser_update(LaserSystem *system)
{
    if (system->cooldown > 0) {
        system->cooldown--;
    }

    for (int i = 0; i < MAX_LASERS; i++) {
        if (system->lasers[i].active) {
            // Move laser
            system->lasers[i].pos.v[0] += system->lasers[i].dir.v[0] * LASER_SPEED;
            system->lasers[i].pos.v[1] += system->lasers[i].dir.v[1] * LASER_SPEED;
            system->lasers[i].pos.v[2] += system->lasers[i].dir.v[2] * LASER_SPEED;

            // Deactivate after timer expires
            system->lasers[i].timer--;
            if (system->lasers[i].timer <= 0) {
                system->lasers[i].active = false;
            }
        }
    }
}

void laser_draw(LaserSystem *system, int frameIdx)
{
    // Setup unlit rendering mode
    rdpq_mode_combiner(RDPQ_COMBINER_FLAT);
    rdpq_set_prim_color(RGBA32(255, 255, 100, 255));
    t3d_state_set_drawflags(T3D_FLAG_DEPTH);

    for (int i = 0; i < MAX_LASERS; i++) {
        if (system->lasers[i].active) {
            // Each laser gets its own matrix slot
            int matIdx = frameIdx * MAX_LASERS + i;
            T3DMat4 laserMat;
            t3d_mat4_identity(&laserMat);
            t3d_mat4_translate(&laserMat,
                system->lasers[i].pos.v[0],
                system->lasers[i].pos.v[1],
                system->lasers[i].pos.v[2]
            );
            t3d_mat4_to_fixed(&system->matrices[matIdx], &laserMat);

            t3d_matrix_push(&system->matrices[matIdx]);
            mesh_draw_cube(system->mesh);
            t3d_matrix_pop(1);
        }
    }
}

Laser* laser_get_array(LaserSystem *system)
{
    return system->lasers;
}
