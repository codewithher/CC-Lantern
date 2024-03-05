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
    Lantern(uint8_t pin, uint8_t numLed, uint8_t brightness);

    /**
     * @brief Starts or restarts LED at current brightness.
     * 
     * To change brightness, use `setBrightness(int brightness)`.
     */
    void begin();

    /**
     * @brief Sets the brightness of the LED.
     * 
     * @param brightness takes input from 0-255 and controls brightness from 
     * darkest `0` to brightest `255`.
     */
    void setBrightness(uint8_t brightness);

    /**
     * @brief Packs red, green, blue values into `uint32` to play nicely with 
     * Adafruit color functions.
     * 
     * @param red 
     * @param green 
     * @param blue 
     * @return uint32_t 
     */
    uint32_t color(uint8_t red, uint8_t green, uint8_t blue);

    /**
     * @brief Set the color using just seconds, red, green, and blue
     * 
     * @param seconds duration to be set
     * @param red how red your color will be
     * @param green how green your color will be
     * @param blue how blue your color will be
     */
    void setColor(float seconds, uint8_t red, uint8_t green, uint8_t blue);

    /**
     * @brief Set the color using Adafruit's `Color()` function.
     * 
     * @param seconds how long the light will stay that color
     * @param color packed RGB color value for the light
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
    static void wait(float seconds);

  private:
    int _pin;
    int _numPixels;
    int _brightness;
    Adafruit_NeoPixel _pixels;
};

#endif