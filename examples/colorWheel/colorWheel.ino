/**
 * Activity 1: Get those lights on!
 * 
 */
#include <Lantern.h>

Lantern lantern;

/**
 * @brief This function only runs once to "setup" the Lantern.
 * 
 */
void setup() {
  lantern.begin();
}

/**
 * @brief This function repeats itself, like a loop!
 * 
 */
void loop() {
  // checkLight();
  rainbowWheel();
}

/**
 * @brief Sets color values for our lantern. Used to check if our Lantern is 
 * ready to accept instructions.
 * 
 * Not getting the color you want? Check out this website to learn how to pick
 * your color using just Red, Green, and Blue!
 * - [RGB Color Picker](https://www.w3schools.com/colors/colors_rgb.asp)
 */
void checkLight() {
  int red = 0;
  int green = 150;
  int blue = 0;
  float seconds = 0.5;

  lantern.setColor(seconds, lantern.colorWheel(32));
}

/**
 * @brief Sets color values for our lantern. Used to check if our lantern is
 * ready to accept instructions.
 * 
 * Instead of using 3 numbers, we can just a single number! This allows us
 * to grab a color from the rainbow if the rainbow was a line from 0-255 
 * starting at red, then going to green, then blue, the finally back to red.
 * 
 */
void checkLightWheel() {
  // Try changing the number to any other number you want!
  lantern.setColor(0.5, lantern.colorWheel(0));
}

/**
 * @brief Sets the color values for our lantern. Goes through all the colors
 * of the rainbow this time!
 * 
 */
void rainbowWheel() {
  for (int i = 0; i < 255; i++) {
    lantern.setColor(0.1, lantern.colorWheel(i));
  }
}