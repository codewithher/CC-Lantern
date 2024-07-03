#ifndef PERLIN_NOISE_H
#define PERLIN_NOISE_H

class PerlinNoise {
public:
    static float noise(float x, float y);
    static float smoothNoise(float x, float y);
    static float interpolate(float a, float b, float x);
    static float interpolatedNoise(float x, float y);
    static float perlinNoise(float x, float y);
};

#endif
