#include <Arduino.h>
#include <Lantern.h>
#include <RNG.h>

Lantern lantern;
RNG rng;

// Creating values outside so that the loop doesn't reset them when fireNoise()
// is finishes.
uint8_t red = 255;
uint8_t green = 0;
uint8_t blue = 0;

// Perlin Noise parameters.
float inc = 0.1;         // Controls the speed of the fire effect.
float start = 0;          // Controls the starting point of the fire effect.

void setup() {
    Serial.begin(9600);
    lantern.begin();
    lantern.setBrightness(5);
}

void loop() {
    // generateNoise();
    // generateNoiseColor();
    fireNoise();
}

/**
 * @brief Open Serial Monitor to see the noise values.
 * 
 */
void generateNoise() {
    for (float x = 0; x < 10; x += 0.1) {
        for (float y = 0; y < 10; y += 0.1) {
            float value = rng.perlinNoise(x, y);
            Serial.println(value);
        }
    }
}

/**
 * @brief Maps the noise values to a color wheel to visually see the noise.
 * 
 */
void generateNoiseColor() {
    for (float x = 0; x < 10; x += 0.1) {
        // Perlin noise generates values between -1 and 1 but map requires
        // integer values, no decimals. To get around this, we multiply the
        // value by 1000 to get a value between -1000 and 1000.
        // We can then remap these values to be between 0 and 255,
        // which is the range of colors.
        const int PRECISION = 1000;
        float value = rng.perlinNoise(x) * PRECISION;
        uint8_t color = map(value, -1 * PRECISION, 1 * PRECISION, 0, 255);
        Serial.print("Color: ");
        Serial.print(color);
        Serial.print(" Value: ");
        Serial.println(value);
        lantern.setColor(0.1, lantern.colorWheel(color));
    }
}

/**
 * @brief Creates a fire effect using perlin noise. Limits the fire effect
 * by changing just the green channel of the rgb color.
 * 
 * To understand why this works, try using the following color slider and only
 * changing the green value to see how the color changes.
 * 
 * https://www.w3schools.com/colors/colors_rgb.asp
 * 
 */
void fireNoise() {
    lantern.setColor(0.1, lantern.color(red, green, blue));
    // Set the starting seed for the fire effect. The max value for the seed is
    // arbitrarily set to 255. It can be any value, but larger values increases
    // the number of random values generated.
    const int SEED_SIZE = 255;

    // Using an offset, we can generate a new set of random values for each
    // iteration of the loop. This ensures that the pattern never truly repeats.
    float xoff = start;

    for (uint8_t x = 0; x < SEED_SIZE; x++) {
        green = rng.perlinNoise(xoff) * 255;
        green = map(green, 0, 255, 0, 155);
        lantern.setColor(0.01, lantern.color(255, green, 0));
        xoff += inc;
        Serial.print("Green: ");
        Serial.println(green);
    }
    start += inc;
}
