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
    
    /**
     * @brief Constructs a new Lantern object with safe default values. Uses 
     * integrated neopixel.
     * 
     */
    Lantern();

    /**
     * @brief Construct a new Lantern object with specified brightness.
     * 
     * @param pin output pin on the adafruit flora.
     * @param numLed number of LED lights.
     * @param brightness takes input from 0-255 and controls brightness from 
     * darkest `0` to brightest `255`.
     */
    Lantern(int pin, int numLed, int brightness);

    /**
     * @brief Starts or restarts LED at current brightness.
     * 
     * To change brightness, use `setBrightness(int brightness)`.
     */
    void begin();

    /**
     * @brief Packs red, green, blue values into `uint32` to play nicely with 
     * Adafruit color functions.
     * 
     * @param red 
     * @param green 
     * @param blue 
     * @return uint32_t 
     */
    static uint32_t color(uint red, uint green, uint blue);

    /**
     * @brief Set the color using just seconds, red, green, and blue
     * 
     * @param seconds duration to be set
     * @param red how red your color will be
     * @param green how green your color will be
     * @param blue how blue your color will be
     */
    void setColor(float seconds, uint red, uint green, uint blue);

    /**
     * @brief Set the color using Adafruit's `Color()` function.
     * 
     * @param seconds how long the light will stay that color
     * @param color 
     */
    void setColor(float seconds, uint32_t color);

    /**
     * @brief Wait for the amount of seconds before continuing. Used to hold 
     * the current color value for some time.
     * 
     * It just calls delay in units of seconds instead of microseconds.
     * 
     * @param seconds 
     */
    void wait(float seconds);

  private:
    int _pin;
    int _numPixels;
    int _brightness;
    Adafruit_NeoPixel _pixels;
};

#endif