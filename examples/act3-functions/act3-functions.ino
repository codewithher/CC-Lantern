/**
 * Activity 3: Make your own patterns!
 */

#include <Lantern.h>

Lantern lantern;

void setup() {
  lantern.begin();
}

void loop() {
  rainbow(20);
}

/**
 * Parameters:
 *   - "seconds": a number that describes how long you want the rainbow gradient to be
 * ---
 * Function Description: This function rotates your LED through the RGB colors (from red to green to blue) by 
 * decreasing each pixel by a value of 1. It will go through the entire rainbow of colors is "seconds" seconds.
 * ---
 * Example Function Call: `rainbowStep(30)` --> creates a rainbow that lasts 30 seconds. 
 */
void rainbow(float seconds) {
  int red = 0; 
  int green = 0;
  int blue = 0;

  // Set default value of 0.25 if an invalid number is given
  if (seconds <= 0) {
    seconds = 0.25;
  }

  const int steps = 255;  // Number of steps for each color in the LED
  const int num_led = 3;  // Number of colors per LED (RGB)  
  const int total_steps = steps * num_led;              // Total steps in the gradient  
  const float time_per_color = seconds / total_steps;   // Time for each color step  

  for (red = 255; red > 0; red--) {
    green += 1;
    lantern.setColor(time_per_color, lantern.color(red, green, blue));
  }

  for (green = 255; green > 0; green--) {
    blue += 1;
    lantern.setColor(time_per_color, lantern.color(red, green, blue));
  }

  for (blue = 255; blue > 0; blue--) {
    red += 1;
    lantern.setColor(time_per_color, lantern.color(red, green, blue));
  }
}

void rainbowWheel() {
  const float duration = 1;
  const int steps = 255;
  for (int i = 0; i < 255; i++) {
    // Generate a random color.
    color current_color = lantern.colorWheel(i);
    Serial.println(current_color);
    lantern.setColor(duration, current_color);
  }
}