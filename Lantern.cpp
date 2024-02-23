#include "Lantern.h"

Lantern::Lantern(int pin, int numPixels) {
  _pin  = pin;
  _numPixels = numPixels;
  _brightness = 50;
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