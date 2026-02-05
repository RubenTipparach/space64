#include "lighting.h"

void lighting_setup_main(void)
{
    uint8_t ambientColor[4] = {0x40, 0x40, 0x50, 0xFF};  // Dim ambient
    uint8_t mainLightColor[4] = {0xA0, 0xA0, 0xB0, 0xFF};  // Cool white main light
    T3DVec3 mainLightDir = {{-0.5f, -1.0f, -0.3f}};
    t3d_vec3_norm(&mainLightDir);

    t3d_light_set_ambient(ambientColor);
    t3d_light_set_directional(0, mainLightColor, &mainLightDir);
}

int lighting_add_laser_lights(Laser *lasers, int maxLasers)
{
    int lightIdx = 1;  // Start after main light

    for (int i = 0; i < maxLasers && lightIdx < 4; i++) {
        if (lasers[i].active) {
            // Light direction = normalized laser position (points to light source)
            T3DVec3 laserLightDir = {{
                lasers[i].pos.v[0],
                lasers[i].pos.v[1],
                lasers[i].pos.v[2]
            }};
            t3d_vec3_norm(&laserLightDir);

            // Brightness fades with distance (inverse square-ish falloff)
            float dist = t3d_vec3_len(&lasers[i].pos);
            float intensity = 50.0f / (dist + 10.0f);
            if (intensity > 1.0f) intensity = 1.0f;
            if (intensity < 0.1f) intensity = 0.1f;

            uint8_t bright = (uint8_t)(0xFF * intensity);
            uint8_t laserLightColor[4] = {bright, (uint8_t)(bright * 0.85f), (uint8_t)(bright * 0.2f), 0xFF};
            t3d_light_set_directional(lightIdx, laserLightColor, &laserLightDir);
            lightIdx++;
        }
    }

    return lightIdx;
}

void lighting_finalize(int lightCount)
{
    t3d_light_set_count(lightCount);
}
