#ifndef AUDIO_H
#define AUDIO_H

#include <libdragon.h>

// Audio channel allocation
#define CHANNEL_AMBIENT 0
#define CHANNEL_LASER   1

// Audio state structure
typedef struct {
    wav64_t *ambient;
    wav64_t *laser;
    bool initialized;
} AudioState;

// Initialize the audio system
void audio_system_init(void);

// Load all game audio assets
AudioState* audio_load_assets(void);

// Play the laser sound effect
void audio_play_laser(AudioState *audio);

// Process audio each frame (call mixer)
void audio_update(void);

#endif // AUDIO_H
