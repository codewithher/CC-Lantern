/**
 * @file Lantern.h
 * @author Ryan (ryan@codewithher.org)
 * @brief Wrapper library for Adafruit_NeoPixel
 * @version 0.1
 * @date 2024-02-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef Lantern_h
#define Lantern_h

#include "Arduino.h"
#include "Adafruit_NeoPixel.h"

class Lantern {
  public:
  Lantern(int pin, int numPixels);
  private:
};

#endif