#include <Lantern.h>

Lantern lantern;

void setup() {
  lantern.begin();
}

void loop() {
  lightOut(5);
  fadingColorOut(5);
  lightOut(3);
  flickeringLights(8);

}

void lightOut(int seconds) {
  int brightness = 0;

  lantern.setBrightness(brightness);
  lantern.wait(seconds);

}

void fadingColorOut(int seconds) {
  int Red = 255;
  int Green = 255;
  int Blue = 255;

  lantern.setBrightness(255);
  lantern.setColor(seconds, lantern.color(Red, Green, Blue));

  easingOut(seconds);
}

void blueLight(int seconds) {
  int Red = 0;
  int Green = 0;
  int Blue = 255;

  lantern.setColor(seconds, lantern.color(Red, Green, Blue));
}

void redLight(int seconds) {
  int Red = 255;
  int Green = 0;
  int Blue = 0;

  lantern.setColor(seconds, lantern.color(Red, Green, Blue));
}

void flickeringLights(int seconds) {
  bool blueTurn = true;
  for(int i = 0; i < seconds; i++) {
    if(blueTurn == true) {
        blueLight(1);
        blueTurn = false;
    }
    else {
        redLight(1);
        blueTurn = true;
    }
  }
}

