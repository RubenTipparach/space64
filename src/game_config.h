#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmath.h>

// Framebuffer count for triple buffering
#define FB_COUNT 3

// Laser configuration
#define MAX_LASERS 8
#define LASER_LIFETIME 180  // ~3 seconds at 60fps
#define LASER_SPEED 2.0f
#define LASER_SPAWN_DISTANCE 12.0f
#define LASER_COOLDOWN_FRAMES 8

// Player configuration
#define PLAYER_ROTATION_SPEED 0.05f
#define STICK_DIVISOR 80.0f

// Cube configuration
#define CUBE_HALF_SIZE 10
#define LASER_CUBE_HALF_SIZE 3

// UV fixed point scale (10.5 format = multiply by 32)
#define UV(x) ((int16_t)((x) * 32))

// Laser state structure
typedef struct {
    T3DVec3 pos;
    T3DVec3 dir;
    int timer;
    bool active;
} Laser;

// Player state structure
typedef struct {
    float rotX;  // Rotation around X axis (up/down)
    float rotY;  // Rotation around Y axis (left/right)
} PlayerState;

#endif // GAME_CONFIG_H
