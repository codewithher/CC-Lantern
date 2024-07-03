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
    generateNoiseColor();
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