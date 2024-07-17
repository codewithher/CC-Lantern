#include <Adafruit_Circuit_Playground.h>
#include <math.h>

#define lantern CircuitPlayground
#define arraySize(x) (sizeof(x) / sizeof((x)[0]))

using color = uint32_t;
using byte = uint8_t;

color green = 0x00FF00;
color red = 0xFF0000;
color off = 0x000000;

void setup() {
  lantern.begin();
  lantern.setBrightness(5);
}

void loop() {
  // tilt();
  tiltLight();
}

/**
 * @brief Prints out the current values of the accelerometer
 * 
 */
void tilt() {
  Serial.print("motionX: ");
  Serial.print(lantern.motionX());
  Serial.print("\tmotionY: ");
  Serial.print(lantern.motionY());
  Serial.print("\tmotionZ: ");
  Serial.print(lantern.motionZ());
  Serial.println();
}

/**
 * @brief Calculates the angle of tilt in the x and y direction
 * 
 */
void tiltLight() {
  color colors[10];

  // motion values
  float x = lantern.motionX();
  float y = lantern.motionY();
  float z = lantern.motionZ();

  // tilt angle in radians
  float theta_x = atan2(x, sqrt(y*y + z*z));
  float theta_y = atan2(y, sqrt(x*x + z*z));

  // convert radians to degrees
  float theta_x_deg = theta_x * 180 / M_PI;
  float theta_y_deg = theta_y * 180 / M_PI;

  Serial.print("theta_x: ");
  Serial.print(theta_x_deg);
  Serial.print("\t");
  Serial.print("theta_y: ");
  Serial.println(theta_y_deg);
  
  lantern.clearPixels();

  // tilt direction
  if (theta_x > 0) {
    lantern.setPixelColor(0, red);
    lantern.setPixelColor(9, red);
  } else {
    lantern.setPixelColor(4, red);
    lantern.setPixelColor(5, red);
  }

  if (theta_y > 0) {
    lantern.setPixelColor(2, red);
  } else {
    lantern.setPixelColor(7, red);
  }
}

/**
 * @brief Sets the colors of the pixels on the lantern based on the given color array.
 * 
 * @param colors The array of colors to set for the pixels
 */
void setPixelColors(color* colors) {
  int pixel_count = 10;
  for (int i = 0; i < pixel_count; i++) {
    lantern.setPixelColor(i, colors[i]);
  }
}