#include "Lantern.h"

Lantern::Lantern() {
  _pin  = 8;            // default is set to #8, integrated neopixel.
  _numPixels = 1;       // assumes single LED.
  _brightness = 50;     // default is set to ~1/5th brightness. Max is 255.
  _pixels  =  Adafruit_NeoPixel(_numPixels, _pin, NEO_GRB + NEO_KHZ800);
}

Lantern::Lantern(int pin, int numPixels, int brightness) {
  _pin  = pin;
  _numPixels = numPixels;
  _brightness = brightness;
  _pixels  =  Adafruit_NeoPixel(_numPixels, _pin, NEO_GRB + NEO_KHZ800);
}

Lantern::begin() {
  _pixels.setBrightness(_brightness);
  _pixels.begin();
}

Lantern::setBrightness(int brightness) {
  _pixels.setBrightness(brightness);  
}

static uint32_t Lantern::color(uint red, uint green, uint blue) {
  return _pixels.Color(red, green, blue);
}

void Lantern::setColor(float seconds, uint red, uint green, uint blue) {
  setColor(seconds, color(red, green, blue));
}

void Lantern::setColor(float seconds, uint32_t color) {
  begin();
  _pixels.setPixelColor(0, color);
  _pixels.show();
  wait(seconds);
}

Lantern::wait(float seconds) {
  const THREE_DAYS = 259200;

  // Bounds check
  if (seconds < 0) {
    Serial.print("Can't wait negative seconds, waiting default of 0.25 seconds");
    seconds = 0.25;
  } else if (seconds > THREE_DAYS) {
    Serial.print("Are you sure you want to keep this color for longer than 3 days? That's a long time!");
  }

  delay(seconds);
}