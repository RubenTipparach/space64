#ifndef LIGHTING_H
#define LIGHTING_H

#include "game_config.h"

// Setup main scene lighting (ambient + directional)
void lighting_setup_main(void);

// Add dynamic lights from active lasers
// Returns the total number of lights (including main light)
int lighting_add_laser_lights(Laser *lasers, int maxLasers);

// Finalize lighting setup with the given light count
void lighting_finalize(int lightCount);

#endif // LIGHTING_H
