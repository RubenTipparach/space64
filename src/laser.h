#ifndef LASER_H
#define LASER_H

#include "game_config.h"
#include "audio.h"

// Laser system state
typedef struct {
    Laser lasers[MAX_LASERS];
    int cooldown;
    T3DVertPacked *mesh;
    T3DMat4FP *matrices;  // FB_COUNT * MAX_LASERS matrices
} LaserSystem;

// Initialize the laser system
LaserSystem* laser_system_create(void);

// Try to fire a laser from the player's current rotation
// Returns true if a laser was fired
bool laser_fire(LaserSystem *system, float rotX, float rotY, AudioState *audio);

// Update all active lasers (movement and lifetime)
void laser_update(LaserSystem *system);

// Draw all active lasers
void laser_draw(LaserSystem *system, int frameIdx);

// Get the array of lasers (for lighting calculations)
Laser* laser_get_array(LaserSystem *system);

#endif // LASER_H
