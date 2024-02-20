#include "Lantern.h"

Lantern::Lantern(int pin, int numPixels) {
  _pin  = pin;
  _numPixels = numPixels;
  _pixels  =  Adafruit_NeoPixel(_numPixels, _pin, NEO_GRB + NEO_KHZ800);
}

Lantern::begin() {
  _pixels.setBrightness(50);
  _pixels.begin();
}