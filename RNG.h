#ifndef RNG_H
#define RNG_H

class RNG {
public:
  static float perlinNoise(float x);
  static float perlinNoise(float x, float y);
  static float random(float min, float max);
  static int random(int min, int max);

private:
  static float noise(float x, float y);
  static float smoothNoise(float x, float y);
  static float interpolate(float a, float b, float x);
  static float interpolatedNoise(float x, float y);
};

#endif
