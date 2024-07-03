#include <Arduino.h>
#include <Lantern.h>
#include <PerlinNoise.h>

Lantern lantern;

uint8_t red = 255;
uint8_t green = 0;
uint8_t blue = 0;
float inc = 0.001;
float start = 0;

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

/**
 * @brief Open Serial Monitor to see the noise values.
 * 
 */
void generateNoise() {
    for (float x = 0; x < 10; x += 0.1) {
        for (float y = 0; y < 10; y += 0.1) {
            float value = PerlinNoise::perlinNoise(x, y);
            Serial.println(value);
        }
    }
}

/**
 * @brief Maps the noise values to a color wheel.
 * 
 */
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

/**
 * @brief Creates a fire effect using perlin noise. Limits rainbow effect 
 * to be within 1/6 of the color wheel, which is red -> yellow.
 * 
 * https://en.wikipedia.org/wiki/Color_wheel
 */
void fireNoise() {
    lantern.setColor(0.1, lantern.color(red, green, blue));
    float xoff = start;
    for (uint8_t x = 0; x < 255; x++) {
        for (uint8_t y = 0; y < 255; y++) {
            green = PerlinNoise::perlinNoise(xoff, 0) * 255;
            green = map(green, 0, 255, 0, 155);
            lantern.setColor(0.001, lantern.color(255, green, 0));
            xoff += inc;
            Serial.print("Green: ");
            Serial.println(green);
        }
        // green  = PerlinNoise::perlinNoise(xoff, 0) * 255;
        // xoff += inc;
    }
    start += inc;

    // // perlinNoise produces a number between -1 and 1.
    // // map takes in integers, so we multiply noise by 1000 to get more precision.
    // const int SCALAR = 5;
    // uint8_t green = 0;
    // for (float x = 0; x < 100; x += 0.1) {
    //     for (float y = 0; y < 100; y += 0.1) {
    //         float value = PerlinNoise::perlinNoise(x, y) * SCALAR;
    //         // green += round(value);
    //         uint8_t green = map(value, -1 * SCALAR, 1 * SCALAR, 0, 150);
    //         Serial.print("Green: ");
    //         Serial.print(green);
    //         Serial.print(" Value: ");
    //         Serial.println(value);
    //         lantern.setColor(0.01, lantern.color(255, green, 0));
    //     }
    // }
}