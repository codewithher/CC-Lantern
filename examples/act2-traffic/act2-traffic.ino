/**
 * Activity 2: Why repeat when you can loop?
 */

#include <Lantern.h>

Lantern lantern;

void setup() {
  lantern.begin();
}

void loop() {
  redlight(1);
  yellowlight(1);
  greenlight(1);
}

void redlight(int seconds) {
  int Red = 150;
  int Green = 0;
  int Blue = 0;
  
  lantern.setColor(seconds, lantern.color(Red, Green, Blue));
}

void yellowlight(int seconds) {
  int Red = 150;
  int Green = 150;
  int Blue = 0;
  
  lantern.setColor(seconds, lantern.color(Red, Green, Blue));
}

void greenlight(int seconds) {
  int Red = 0;
  int Green = 150;
  int Blue = 0;
  
  lantern.setColor(seconds, lantern.color(Red, Green, Blue));
}