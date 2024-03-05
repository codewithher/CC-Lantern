#include "Lantern.h"

Lantern::Lantern() {
  _pin  = 8;            // default is set to #8, integrated neopixel.
  _numPixels = 1;       // assumes single LED.
  _brightness = 50;     // default is set to ~1/5th brightness. Max is 255.
  _pixels  =  Adafruit_NeoPixel(_numPixels, _pin, NEO_GRB + NEO_KHZ800);
}

Lantern::Lantern(uint8_t pin, uint8_t numPixels, uint8_t brightness) {
  _pin  = pin;
  _numPixels = numPixels;
  _brightness = brightness;
  _pixels  =  Adafruit_NeoPixel(_numPixels, _pin, NEO_GRB + NEO_KHZ800);
}

void Lantern::begin() {
  _pixels.setBrightness(_brightness);
  _pixels.begin();
}

void Lantern::setBrightness(uint8_t brightness) {
  _pixels.setBrightness(brightness);  
}

static uint32_t Lantern::color(uint8_t red, uint8_t green, uint8_t blue) {
  // The red, green, and blue values are bitwise ANDed with 0xFF to ensure they 
  // fit within the range of 0-255, and then left-shifted and combined using 
  // bitwise OR operations.

  // a 32-bit color is composed of 8-bit red, green, and blue values
  // | RED      | GREEN   | BLUE   |
  // | 32 -> 24 | 24 -> 16 | 16 -> 8 |
  const uint8_t MAX = 255;
  return ((red & MAX) << 24) | ((green & MAX) << 16) | (blue & MAX) << 8;
}

void Lantern::setColor(float seconds, uint8_t red, uint8_t green, uint8_t blue) {
  setColor(seconds, color(red, green, blue));
}

void Lantern::setColor(float duration, uint32_t color) {
  _pixels.setPixelColor(0, color);
  _pixels.show();
  wait(duration);
}

static void Lantern::wait(float seconds) {
  static const float THREE_DAYS = 259200;
  // Bounds check
  if (seconds < 0) {
    Serial.print("Can't wait negative seconds, waiting default of 0.25 seconds");
    seconds = 0.25;
  } else if (seconds > THREE_DAYS) {
    Serial.print("Are you sure you want to keep this color for longer than 3 days? That's a long time!");
  }

  delay(int(seconds * 1000));
}
