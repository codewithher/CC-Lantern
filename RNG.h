#ifndef RNG_H
#define RNG_H

class RNG {
public:
  /**
   * @brief Implements 1D Perlin Noise. Generates a random value between -1 and 1.
   * For smooth randomness, use `perlinNoise(float x)` in a loop. Control the 
   * speed of the noise by changing the size of the loop steps. Bigger steps ->
   * bigger changes in noise. Try starting at a step size of 0.1.
   * 
   * @param x 
   * @return float 
   */
  static float perlinNoise(float x);

  /**
   * @brief Implements 2D Perlin Noise. Generates a random value between -1 and 1.
   * For smooth randomness, use `perlinNoise(float x, float y)` in a loop. Control the 
   * speed of the noise by changing the size of the loop steps. Bigger steps ->
   * bigger changes in noise. Try starting at a step size of 0.1.
   * 
   * @param x 
   * @return float 
   */
  static float perlinNoise(float x, float y);

  /**
   * @brief Generates a random float between min and max.
   * 
   * @param min 
   * @param max 
   * @return float 
   */
  static float random(float min, float max);

  /**
   * @brief Generates a random int between min and max.
   * 
   * @param min 
   * @param max 
   * @return int 
   */
  static int random(int min, int max);

private:
  static float noise(float x, float y);
  static float smoothNoise(float x, float y);
  static float interpolate(float a, float b, float x);
  static float interpolatedNoise(float x, float y);
};

#endif
