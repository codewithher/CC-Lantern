#include "Lantern.h"

Lantern::Lantern() {
  _pin  = 8;            // default is set to #8, integrated neopixel.
  _numPixels = 1;       // assumes single LED.
  _brightness = 50;     // default is set to ~1/5th brightness. Max is 255.
  _pixels  =  Adafruit_NeoPixel(_numPixels, _pin, NEO_GRB + NEO_KHZ800);
}

Lantern::Lantern(byte pin, byte numPixels, byte brightness) {
  _pin  = pin;
  _numPixels = numPixels;
  _brightness = brightness;
  _pixels  =  Adafruit_NeoPixel(_numPixels, _pin, NEO_GRB + NEO_KHZ800);
}

void Lantern::begin() {
  _pixels.setBrightness(_brightness);
  _pixels.begin();
}

void Lantern::setBrightness(byte brightness) {
  _pixels.setBrightness(brightness);  
}

color Lantern::rgb(byte red, byte green, byte blue) {
  // The red, green, and blue values are bitwise ANDed with 0xFF to ensure they 
  // fit within the range of 0-255, and then left-shifted and combined using 
  // bitwise OR operations.

  // a 32-bit color is composed of 8-bit red, green, and blue values
  // | RED      | GREEN   | BLUE   |
  // | 32 -> 24 | 24 -> 16 | 16 -> 8 |
  return _pixels.Color(red, green, blue);
}

void Lantern::setColor(float seconds, byte red, byte green, byte blue) {
  setColor(seconds, color(red, green, blue));
}

void Lantern::setColor(float duration, color color) {
  _pixels.setPixelColor(0, color);
  _pixels.show();
  wait(duration);
}

static void Lantern::wait(float seconds) {
  static const float THREE_DAYS = 259200;
  // Bounds check
  if (seconds < 0) {
    Serial.println("Can't wait negative seconds, waiting default of 0.25 seconds");
    seconds = 0.25;
  } else if (seconds > THREE_DAYS) {
    Serial.println("Are you sure you want to keep this color for longer than 3 days? That's a long time!");
  }

  delay(int(seconds * 1000));
}

color Lantern::colorWheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return _pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return _pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return _pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}