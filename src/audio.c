#include "audio.h"

static AudioState audioState = {0};

void audio_system_init(void)
{
    audio_init(44100, 4);
    mixer_init(8);
    wav64_init_compression(1);  // vadpcm compression
}

AudioState* audio_load_assets(void)
{
    audioState.ambient = wav64_load("rom:/surrealism-ambient-mix.wav64", NULL);
    audioState.laser = wav64_load("rom:/laser7.wav64", NULL);

    // Start ambient music if loaded successfully
    if (audioState.ambient && audioState.laser) {
        audioState.initialized = true;
        wav64_set_loop(audioState.ambient, true);
        wav64_play(audioState.ambient, CHANNEL_AMBIENT);
        mixer_ch_set_vol(CHANNEL_AMBIENT, 0.5f, 0.5f);
    }

    return &audioState;
}

void audio_play_laser(AudioState *audio)
{
    if (audio && audio->laser) {
        wav64_play(audio->laser, CHANNEL_LASER);
    }
}

void audio_update(void)
{
    mixer_try_play();
}
