/**
 * Space64 - N64 Game
 * Built with libdragon + tiny3d
 */

#include "game_config.h"
#include "audio.h"
#include "camera.h"
#include "lighting.h"
#include "player.h"
#include "laser.h"

int main(void)
{
    // Debug initialization
    debug_init_isviewer();
    debug_init_usblog();

    // Initialize filesystem
    dfs_init(DFS_DEFAULT_LOCATION);

    // Initialize input
    joypad_init();

    // Initialize display
    display_init(RESOLUTION_320x240, DEPTH_16_BPP, FB_COUNT, GAMMA_NONE, FILTERS_RESAMPLE);
    rdpq_init();
    t3d_init((T3DInitParams){});

    // Initialize subsystems
    audio_system_init();
    AudioState *audio = audio_load_assets();

    // Load UI font
    rdpq_font_t *font = rdpq_font_load_builtin(FONT_BUILTIN_DEBUG_MONO);
    rdpq_text_register_font(1, font);

    // Create game objects
    Camera camera = camera_create();
    Player *player = player_create();
    LaserSystem *lasers = laser_system_create();

    int frameIdx = 0;

    // Main game loop
    for (;;)
    {
        // Cycle frame buffer index
        frameIdx = (frameIdx + 1) % FB_COUNT;

        // Poll input
        joypad_poll();
        joypad_buttons_t pressed = joypad_get_buttons_pressed(JOYPAD_PORT_1);
        joypad_inputs_t inputs = joypad_get_inputs(JOYPAD_PORT_1);

        // Update game state
        player_update(player, inputs);

        if (pressed.a) {
            laser_fire(lasers, player_get_rot_x(player), player_get_rot_y(player), audio);
        }

        laser_update(lasers);

        // Update transforms
        camera_update(&camera);
        player_update_matrix(player, frameIdx);

        // Begin frame
        rdpq_attach(display_get(), display_get_zbuf());
        t3d_frame_start();
        camera_attach(&camera);

        t3d_screen_clear_color(RGBA32(10, 10, 30, 0xFF));
        t3d_screen_clear_depth();

        // Setup lighting
        lighting_setup_main();
        int lightCount = lighting_add_laser_lights(laser_get_array(lasers), MAX_LASERS);
        lighting_finalize(lightCount);

        // Draw game objects
        player_draw(player, frameIdx);
        laser_draw(lasers, frameIdx);

        // Draw UI
        rdpq_sync_pipe();
        rdpq_set_mode_standard();
        rdpq_text_print(NULL, 1, 100, 20, "SPACE64");
        rdpq_text_print(NULL, 1, 50, 220, "Press A to fire lasers!");

        rdpq_detach_show();

        // Process audio
        audio_update();
    }

    t3d_destroy();
    return 0;
}
