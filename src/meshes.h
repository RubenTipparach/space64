#ifndef MESHES_H
#define MESHES_H

#include "game_config.h"

// Create a textured cube mesh with the given texture dimensions
T3DVertPacked* mesh_create_cube(int texWidth, int texHeight);

// Create a small laser projectile cube with vertex colors
T3DVertPacked* mesh_create_laser_cube(void);

// Draw a cube mesh (6 faces)
void mesh_draw_cube(T3DVertPacked *verts);

#endif // MESHES_H
