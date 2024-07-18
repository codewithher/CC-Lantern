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
  Serial.begin(9600);
  lantern.begin();
  lantern.setBrightness(5);
}

void loop() {
  if (lantern.leftButton()) {
    // print out the accelerometer values
    tiltAccel();
  } else if (lantern.rightButton()) {
    // print out the tilt angle
    tiltAngle();
  }
  tiltLight();
}

/**
 * @brief Prints out the current values of the accelerometer
 * 
 */
void tiltAccel() {
  Serial.print("motionX: ");
  Serial.print(lantern.motionX());
  Serial.print("\t");
  Serial.print("motionY: ");
  Serial.print(lantern.motionY());
  Serial.print("\t");
  Serial.print("motionZ: ");
  Serial.print(lantern.motionZ());
  Serial.println();
}

void tiltAngle() {
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
  Serial.print(theta_y_deg);
  Serial.println();
}

/**
 * @brief Calculates the angle of tilt in the x and y direction
 * 
 */
void tiltLight() {
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
    lantern.setPixelColor(1, red);
    lantern.setPixelColor(2, red);
    lantern.setPixelColor(3, red);
  } else {
    lantern.setPixelColor(6, red);
    lantern.setPixelColor(7, red);
    lantern.setPixelColor(8, red);
  }
}