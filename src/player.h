#ifndef PLAYER_H
#define PLAYER_H

#include "game_config.h"

// Player rendering resources
typedef struct {
    PlayerState state;
    T3DVertPacked *mesh;
    T3DMat4FP *matrices;  // FB_COUNT matrices
    sprite_t *texture;
} Player;

// Create and initialize player
Player* player_create(void);

// Update player rotation based on joystick input
void player_update(Player *player, joypad_inputs_t inputs);

// Get the player's current model matrix for the frame
void player_update_matrix(Player *player, int frameIdx);

// Draw the player cube
void player_draw(Player *player, int frameIdx);

// Get player rotation values
float player_get_rot_x(Player *player);
float player_get_rot_y(Player *player);

#endif // PLAYER_H
