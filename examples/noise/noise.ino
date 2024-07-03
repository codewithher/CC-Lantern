#include <Arduino.h>
#include <Lantern.h>
#include <PerlinNoise.h>

Lantern lantern;

void setup() {
    Serial.begin(9600);
    lantern.begin();
}

void loop() {
    for (float x = 0; x < 10; x += 0.1) {
        for (float y = 0; y < 10; y += 0.1) {
            float value = PerlinNoise::perlinNoise(x, y);
            Serial.println(value);
        }
    }
    delay(1000);
}
