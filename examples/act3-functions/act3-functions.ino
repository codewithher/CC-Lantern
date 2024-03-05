/**
 * Activity 3: Make your own patterns!
 */

#include <Lantern.h>

Lantern lantern();

void setup() {
  lantern.begin();
}

void loop() {
  // try hovering over these functions!
  gradientRed(1.5, 10);
  blinkingPatterns(2, 2, 10);
  fadeInAndOut(1.5, 1.5);
}

/**
 * Parameters:
 *   - "seconds": a number that describes how long you want each "iteration" to be
 *   - "numSteps": a number that describes how many times you want the red color to change
 * ---
 * Function Description: This function sets your LED to white (aka all RGB values to 255) and decreases 
 *   the red RGB value by 10 a "numSteps" amount of times. It will decrease the value every "seconds" seconds.
 * ---
 * Example Function Call: `gradientRed(2,4)` --> this decreases the red RBG value every 2 seconds, for 4 times
 */
void gradientRed(float seconds, int numSteps) {
  int Red = 250;
  int Green = 250;
  int Blue = 250;

  for (int step = 0; step < numSteps; step++) {
    Red -= 50;
    lantern.setColor(seconds, lantern.color(Red, Green, Blue));
  }
}

/*
 * Parameters:
 *   - "seconds": a number that describes how long you want each "iteration" to be
 *   - "numSteps": a number that describes how many times you want the green color to change
 * ---
 * Function Description: This function sets your LED to white (aka all RGB values to 255) and decreases 
 *   the green RGB value by 10 a "numSteps" amount of times. It will decrease the value every "seconds" seconds.
 * ---
 * Example Function Call: `gradientGreen(2,4)` --> this decreases the green RBG value every 2 seconds, for 4 times
 */
void gradientGreen(float seconds, int numSteps) {
  int Red = 250;
  int Green = 250;
  int Blue = 250;

  for (int step = 0; step < numSteps; step++) {
    Green -= 50;
    lantern.setColor(seconds, lantern.color(Red, Green, Blue));
  }
}

/*
 * Parameters:
 *   - "seconds": a number that describes how long you want each "iteration" to be
 *   - "numSteps": a number that describes how many times you want the blue color to change
 * ---
 * Function Description: This function sets your LED to white (aka all RGB values to 255) and decreases 
 *   the blue RGB value by 10 a "numSteps" amount of times. It will decrease the value every "seconds" seconds.
 * ---
 * Example Function Call: `gradientBlue(2,4)` --> this decreases the blue RBG value every 2 seconds, for 4 times
 */
void gradientBlue(float seconds, int numSteps) {
  int Red = 250;
  int Green = 250;
  int Blue = 250;

  for (int step = 0; step < numSteps; step++) {
    Blue -= 50;
    lantern.setColor(seconds, lantern.color(Red, Green, Blue));
  }
}

/*
 * Parameters:
 *   - "seconds": a number that describes how long you want the LED to stay on and off each blink
 *   - "num_blinks": a number that describes how many times you want the LED to blink
 * ---
 * Function Description: This function makes your LED blink "num_blinks" amount of times with the LED on and
 *   off for "seconds" amount of seconds.
 * ---
 * Example Function Call: `blinkingPatterns(1,10)` --> this makes the LED blink on and off for 1 second each, 10 times
 */
void blinkingPatterns(float on_time, float off_time, int num_blinks) {
  int Red = 255;
  int Green = 255;
  int Blue = 255;

  for (int i = 0; i < num_blinks; i++) {
    // Turn the LED on
    lantern.setColor(on_time, lantern.color(Red, Green, Blue));
    
    // Turn the LED off by lowering colors to 0
    lantern.setColor(off_time, lantern.color(0, 0, 0));
  }
}

/*
 * Parameters:
 *   - "fadeInSeconds": a number that describes how long it takes for the LED to increase in brightness a little more
 *   - "fadeOutSeconds": a number that describes how long it takes for the LED to decrease in brightness a little more
 * ---
 * Function Description: This function makes your LED fade in with the brightness changing every "fadeInSeconds"
 *   seconds and then fade out with the brightness changing every "fadeOutSeconds" seconds
 * ---
 * Example Function Call: `fadeInAndOut(1,2)` --> this makes the LED fade in with the brightness chaning every 1 second
 *   and then fade out with the brighness changing every 2 seconds
 */
void fadeInAndOut(float fadeInSeconds, float fadeOutSeconds) {
  fadeIn(fadeInSeconds);
  fadeOut(fadeOutSeconds);
}

/*
 * Parameters:
 *   - "seconds": a number that describes how long it takes for the LED to fade brightness a little more
 * ---
 * Function Description: This function makes your LED slowly get brighter each "seconds" number of seconds
 * ---
 * Example Function Call: `fadeIn(1)` --> this increases the brightness a little every second
 */
void fadeIn(float seconds) {
  int Red = 150;
  int Green = 0;
  int Blue = 0;
  int brightnessStep = 5;     // how much we decrease brightness by
  int brightnessStart = 200;  // how much we start brightness at
  int brightnessMaxStep = brightnessStart / brightnessStep;  // how many steps it takes

  // Fade Out
  for (int step = 0; step < brightnessMaxStep; step++) {
    lantern.setBrightness(brightnessStart - (step * brightnessStep));
    lantern.setColor(seconds, lantern.color(Red, Green, Blue));
  }
}

/*
 * Parameters:
 *   - "seconds": a number that describes how long it takes for the LED to fade brightness a little more
 * ---
 * Function Description: This function makes your LED slowly get darker each "seconds" number of seconds
 * ---
 * Example Function Call: `fadeOut(1)` --> this decreases the brightness a little every second
 */
void fadeOut(float seconds) {
  int Red = 255;
  int Green = 120;
  int Blue = 0;
  int brightnessStep = 5;    // how much we decrease brightness by
  int brightnessStart = 200;  // how much we start brightness at
  int brightnessMaxStep = brightnessStart / brightnessStep;  // how many steps it takes

  // Fade Out
  for (int step = 0; step < brightnessMaxStep; step++) {
    lantern.setBrightness(brightnessStart - (step * brightnessStep));
    lantern.setColor(seconds, lantern.color(Red, Green, Blue));
  }
}

/*
 * Parameters:
 *   - "seconds": a number that describes how long it takes for the LED to fade brightness a little more
 *   - "numPulses": how many times you want the LED to fade in and out
 * --- 
 * Function Description: This function makes your LED slowly turn all the way on and all the way off a "numPulses"
 *   amount of times, with the brightness changing every "seconds" amount of seconds
 * ---
 * Example Function Call: `pulsatingEffect(1,2)` --> this makes the LED turn on and off 2 times with the brightness
 *   changing every 1 second
 */
void pulsatingEffect(int seconds, int numPulses) {
  int Red = 150;
  int Green = 0;
  int Blue = 0;
  int brightnessStart = 200;  // how much we start brightness at

  for (int i = 0; i < numPulses; i++) {
    for (int brightness = 0; brightness <= brightnessStart; brightness++) {
      lantern.setBrightness(brightness);
      lantern.setColor(seconds, lantern.color(Red, Green, Blue));
    }
    
    for (int brightness = brightnessStart; brightness >= 0; brightness--) {
      lantern.setBrightness(brightness);
      lantern.setColor(seconds, lantern.color(Red, Green, Blue));
    }
  }
}