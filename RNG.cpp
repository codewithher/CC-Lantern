#include "RNG.h"
#include <math.h>

float RNG::noise(float x, float y) {
int n = (int)x + (int)y * 57;
n = (n << 13) ^ n;
return (1.0 - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
}

float RNG::smoothNoise(float x, float y) {
float corners = (noise(x-1, y-1) + noise(x+1, y-1) + noise(x-1, y+1) + noise(x+1, y+1)) / 16;
float sides = (noise(x-1, y) + noise(x+1, y) + noise(x, y-1) + noise(x, y+1)) / 8;
float center = noise(x, y) / 4;
return corners + sides + center;
}

float RNG::interpolate(float a, float b, float x) {
float ft = x * 3.1415927;
float f = (1 - cos(ft)) * 0.5;
return a * (1 - f) + b * f;
}

float RNG::interpolatedNoise(float x, float y) {
int integer_X = (int)x;
float fractional_X = x - integer_X;

int integer_Y = (int)y;
float fractional_Y = y - integer_Y;

float v1 = smoothNoise(integer_X, integer_Y);
float v2 = smoothNoise(integer_X + 1, integer_Y);
float v3 = smoothNoise(integer_X, integer_Y + 1);
float v4 = smoothNoise(integer_X + 1, integer_Y + 1);

float i1 = interpolate(v1, v2, fractional_X);
float i2 = interpolate(v3, v4, fractional_Y);

return interpolate(i1, i2, fractional_Y);
}

float RNG::perlinNoise(float x) {
float total = 0;
float persistence = 0.5;
int octaves = 4;
for (int i = 0; i < octaves; i++) {
    float frequency = pow(2, i);
    float amplitude = pow(persistence, i);
    total += interpolatedNoise(x * frequency, 0) * amplitude;
}
return total;
}

float RNG::perlinNoise(float x, float y) {
float total = 0;
float persistence = 0.5;
int octaves = 4;

for (int i = 0; i < octaves; i++) {
    float frequency = pow(2, i);
    float amplitude = pow(persistence, i);

    total += interpolatedNoise(x * frequency, y * frequency) * amplitude;
}

return total;
}
