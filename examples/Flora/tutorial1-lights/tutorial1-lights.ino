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
  lantern.setBrightness(5);
}

/**
 * @brief This function repeats itself, like a loop!
 * 
 */
void loop() {
  checkLight();
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
  // Set color values here! Colors range from 0 to 255
  byte red = 0;
  byte green = 150;
  byte blue = 0;
  float seconds = 0.5;

  lantern.setColor(seconds, lantern.rgb(red, green, blue));
}