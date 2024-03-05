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
  int red = 0;
  int green = 150;
  int blue = 0;
  float seconds = 0.5;

  lantern.setColor(seconds, lantern.color(red, green, blue));
}