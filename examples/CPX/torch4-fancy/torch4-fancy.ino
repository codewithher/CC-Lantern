///////////////////////////////////////////////////////////////////////////////
// PART 1: Imports / Globals  /////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#include <Adafruit_CircuitPlayground.h>
#include <math.h>

#define lantern CircuitPlayground
#define arraySize(x) (sizeof(x) / sizeof((x)[0]))

using color = uint32_t;
using byte = uint8_t;

color red     = 0xFF0000; // Red, representing cooler flames at the top
color orange  = 0xFF5800; // Orange, representing warm flames
color yellow  = 0xFFFF00; // Yellow, representing hot flames
color white   = 0xFFFFFF; // White, representing the peak heat at the bottom
color off     = 0x000000; // Off, representing no heat

const int num_pixels = 10;

///////////////////////////////////////////////////////////////////////////////
// PART 2: Setup and Loop /////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(9600);
  lantern.begin();
  lantern.setBrightness(5);
}

void loop() {
  tiltFire();
}

///////////////////////////////////////////////////////////////////////////////
// PART 3: Functions  /////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/**
 * @brief Uses polar coordinates to determine the tilt of the lantern and 
 * displays a single pixel the direction closest to the sky.
 * 
 */
void skyPointer() {
  const float x = lantern.motionX();
  const float y = lantern.motionY();
  const float z = lantern.motionZ();

  const float theta = atan2(y, x);
  // to determine the opposite direction (like the ground), we can inverse the 
  // radians by swapping the left and right half of the array.
  const float radians[num_pixels] = {
      M_PI*1/6,   M_PI*2/6,   M_PI*3/6,   M_PI*4/6,   M_PI*5/6, // Left half
    0-M_PI*5/6, 0-M_PI*4/6, 0-M_PI*3/6, 0-M_PI*2/6, 0-M_PI*1/6  // Right half
  };
  float difference[num_pixels] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  // to increase the amount of pixels that are lit up, we can increase the
  // threshold value. 
  //    0.3 = 1 pixel
  //    0.7 = 2-3 pixels
  const float threshold = 0.3;

  // assign single pixel based on difference between theta and radians
  for (int i = 0; i < num_pixels; i++) {
    const float diff = abs(theta - radians[i]);
    difference[i] = diff;
    if (diff <= threshold) {
      lantern.setPixelColor(i, red);
    } else {
      lantern.setPixelColor(i, off);
    }
  }
}

/**
 * @brief Uses thresholds to determine the heat of the pixels based on the tilt
 * 
 */
void tiltFire() {  float x = lantern.motionX();
  float y = lantern.motionY();
  float z = lantern.motionZ();

  float theta = atan2(y, x);
  // original radians for sky pointer
  float radiansSky[10] = {
      M_PI*1/6,   M_PI*2/6,   M_PI*3/6,   M_PI*4/6,   M_PI*5/6, // Left half
    0-M_PI*5/6, 0-M_PI*4/6, 0-M_PI*3/6, 0-M_PI*2/6, 0-M_PI*1/6  // Right half
  };
  // inverse radians to determine the direction closest to the ground
  float radiansGnd[10] = {
    0-M_PI*5/6, 0-M_PI*4/6, 0-M_PI*3/6, 0-M_PI*2/6, 0-M_PI*1/6,  // Right half
      M_PI*1/6,   M_PI*2/6,   M_PI*3/6,   M_PI*4/6,   M_PI*5/6   // Left half
  };
  float differenceSky[10]  = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  float differenceGnd[10]  = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  // assign single pixel based on difference between theta and radians
  for (int i = 0; i < 10; i++) {
    float diffSky = abs(theta - radiansSky[i]);
    float diffGnd = abs(theta - radiansGnd[i]);
    differenceSky[i] = diffSky;
    differenceGnd[i] = diffGnd;
    if (diffSky <= 0.7) {
      lantern.setPixelColor(i, red);
    }
    if (diffGnd <= 0.7) {
      lantern.setPixelColor(i, white);
    } 
    if (diffSky > 0.7 && diffGnd > 0.7) {
      lantern.setPixelColor(i, yellow);
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
// PART 4: Helper Functions ///////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
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
 * @brief Prints the contents of angle arrays
 * 
 * @param arr The array to print
 */
void printArray(float* arr, int size) {
  for (int i = 0; i < size; i++) {
    Serial.print(arr[i]);
    Serial.print(" ");
  }
  Serial.println();
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