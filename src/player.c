#include "player.h"
#include "meshes.h"

static Player player = {0};

Player* player_create(void)
{
    player.state.rotX = 0.0f;
    player.state.rotY = 0.0f;

    // Load texture
    player.texture = sprite_load("rom:/test.sprite");

    // Create mesh with texture dimensions
    player.mesh = mesh_create_cube(player.texture->width, player.texture->height);

    // Allocate matrices
    player.matrices = malloc_uncached(sizeof(T3DMat4FP) * FB_COUNT);

    return &player;
}

void player_update(Player *player, joypad_inputs_t inputs)
{
    float stickX = inputs.stick_x / STICK_DIVISOR;
    float stickY = inputs.stick_y / STICK_DIVISOR;

    player->state.rotY += stickX * PLAYER_ROTATION_SPEED;
    player->state.rotX -= stickY * PLAYER_ROTATION_SPEED;
}

void player_update_matrix(Player *player, int frameIdx)
{
    t3d_mat4fp_from_srt_euler(&player->matrices[frameIdx],
        (float[3]){1.0f, 1.0f, 1.0f},
        (float[3]){player->state.rotX, player->state.rotY, 0.0f},
        (float[3]){0.0f, 0.0f, 0.0f}
    );
}

void player_draw(Player *player, int frameIdx)
{
    // Upload texture
    rdpq_sync_pipe();
    rdpq_sync_tile();
    rdpq_sprite_upload(TILE0, player->texture, NULL);

    // Setup lit textured mode
    rdpq_mode_combiner(RDPQ_COMBINER_TEX_SHADE);
    rdpq_mode_filter(FILTER_BILINEAR);
    t3d_state_set_drawflags(T3D_FLAG_TEXTURED | T3D_FLAG_SHADED | T3D_FLAG_DEPTH);

    t3d_matrix_push(&player->matrices[frameIdx]);
    mesh_draw_cube(player->mesh);
    t3d_matrix_pop(1);
}

float player_get_rot_x(Player *player)
{
    return player->state.rotX;
}

float player_get_rot_y(Player *player)
{
    return player->state.rotY;
}
