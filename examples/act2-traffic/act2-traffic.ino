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

void redlight(float seconds) {
  byte red = 150;
  byte green = 0;
  byte blue = 0;
  
  lantern.setColor(seconds, lantern.rgb(red, green, blue));
}

void yellowlight(float seconds) {
  byte red = 150;
  byte green = 150;
  byte blue = 0;
  
  lantern.setColor(seconds, lantern.rgb(red, green, blue));
}

void greenlight(float seconds) {
  byte red = 0;
  byte green = 150;
  byte blue = 0;
  
  lantern.setColor(seconds, lantern.rgb(red, green, blue));
}