#include <Arduino.h>
#include <Lantern.h>
#include <PerlinNoise.h>

Lantern lantern;

void setup() {
    Serial.begin(9600);
    lantern.begin();
    lantern.setBrightness(5);
}

void loop() {
    // generateNoiseColor();
    // checkFireColors();
    fireNoise();
}

void generateNoise() {
    for (float x = 0; x < 10; x += 0.1) {
        for (float y = 0; y < 10; y += 0.1) {
            float value = PerlinNoise::perlinNoise(x, y);
            Serial.println(value);
        }
    }
}

void generateNoiseColor() {
    for (float x = 0; x < 10; x += 0.1) {
        for (float y = 0; y < 10; y += 0.1) {
            const int SIGDIGITS = 1000;
            float value = PerlinNoise::perlinNoise(x, y)*SIGDIGITS;
            uint8_t color = map(value, -1*SIGDIGITS, 1*SIGDIGITS, 0, 255);
            Serial.print("Color: ");
            Serial.print(color);
            Serial.print(" Value: ");
            Serial.println(value);
            lantern.setColor(0.1, lantern.colorWheel(color));
        }
    }
}

void checkFireColors() {
    for (int i = 0; i < 255; i++) {
        lantern.setColor(0.07, lantern.color(255, i, 0));
    }
}

/**
 * @brief Creates a fire effect using perlin noise. Limits rainbow effect 
 * to be within 1/6 of the color wheel, which is red -> yellow.
 * 
 * https://en.wikipedia.org/wiki/Color_wheel
 */
void fireNoise() {
    const uint8_t red_lower = 0;
    const uint8_t red_upper = 255/6;
    // perlinNoise produces a number between -1 and 1.
    // map takes in integers, so we multiply noise by 1000 to get more precision.
    const int SCALAR = 5;
    uint8_t green = 0;
    for (float x = 0; x < 100; x += 0.1) {
        for (float y = 0; y < 100; y += 0.1) {
            float value = PerlinNoise::perlinNoise(x, y) * SCALAR;
            // green += round(value);
            uint8_t green = map(value, -1 * SCALAR, 1 * SCALAR, 0, 150);
            Serial.print("Green: ");
            Serial.print(green);
            Serial.print(" Value: ");
            Serial.println(value);
            lantern.setColor(0.01, lantern.color(255, green, 0));
        }
    }
}