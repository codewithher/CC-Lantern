#include <Adafruit_CircuitPlayground.h>
#include <math.h>

#define lantern CircuitPlayground
#define arraySize(x) (sizeof(x) / sizeof((x)[0]))

using color = uint32_t;
using byte = uint8_t;

const color red    = 0xFF0000;
const color orange = 0xFF5800;
const color yellow = 0xFFFF00;
const color white  = 0xFFFFFF;
const color off    = 0x000000;

const int num_pixels = 10;

void setup() {
  Serial.begin(9600);
  lantern.begin();
  lantern.setBrightness(5);
}

void loop() {
  // Use skypointer by default
  // Use tiltShift when left or right button is pressed
  skyPointer();
  if (lantern.leftButton()) {
    tiltShift();
  } else if (lantern.rightButton()) {
    tiltShift();
  }
}

/**
 * @brief Uses polar coordinates to determine the tilt of the lantern and 
 * displays a single pixel the direction closest to the sky.
 * 
 */
void skyPointer() {
  const float x = lantern.motionX();
  const float y = lantern.motionY();
  const float z = lantern.motionZ();

  // calculate the radian angle of the lantern
  const float theta = atan2(y, x); 

  // the radian angles of the lantern
  // to determine the opposite direction (like the ground), we can inverse the 
  // radians by swapping the left and right half of the array.
  const float radians[num_pixels] = {
      M_PI*1/6,   M_PI*2/6,   M_PI*3/6,   M_PI*4/6,   M_PI*5/6, // Left half
    0-M_PI*5/6, 0-M_PI*4/6, 0-M_PI*3/6, 0-M_PI*2/6, 0-M_PI*1/6  // Right half
  };
  float difference[num_pixels] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  
  // find the pixel ID that is closest to the sky
  const int sky_index = findClosest(radians, num_pixels, theta);
  Serial.print("sky_index: ");
  Serial.println(sky_index);
  
  // to increase the amount of pixels that are lit up, we can increase the
  // threshold value. 
  //    0.2 = 1 pixel
  //    0.7 = 2-3 pixels
  const float thresold = 0.2;
  
  // assign single pixel based on difference between theta and radians
  for (int i = 0; i < num_pixels; i++) {
    const float diff = abs(theta - radians[i]);
    difference[i] = diff;
    if (diff <= thresold) {
      lantern.setPixelColor(i, red);
    } else {
      lantern.setPixelColor(i, off);
    }
  }
}

/**
 * @brief Uses polar coordinates to determine the tilt of the lantern and
 * shifts the pattern to the left or right based on the tilt.
 * 
 */
void tiltShift() {
  const float x = lantern.motionX();
  const float y = lantern.motionY();
  const float z = lantern.motionZ();

  // calculate the radian angle of the lantern
  const float theta = atan2(y, x);

  const float radians[num_pixels] = {
      M_PI*1/6,   M_PI*2/6,   M_PI*3/6,   M_PI*4/6,   M_PI*5/6, // Left half
    0-M_PI*5/6, 0-M_PI*4/6, 0-M_PI*3/6, 0-M_PI*2/6, 0-M_PI*1/6  // Right half
  };

  // track the difference between the real angle and the radians angle
  float difference[num_pixels] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  // this is the color pattern that will be shifted based on the tilt
  const color pattern[num_pixels] = {
    red, orange, orange, yellow, white, white, yellow, orange, orange, red
  };

  // find the pixel ID that is closest to the sky
  const int sky_index = findClosest(radians, num_pixels, theta);
  // shift until we move the sky_index to the top of the array

  const int shift_amount = top_index;
  Serial.print("shift_amount: ");
  Serial.println(shift_amount);

  arrayShift(pattern, num_pixels, shift_amount);
  setPixelColors(pattern);
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

int findClosest(float* arr, int size, float value) {
  int closest = 0;
  float minDiff = abs(value - arr[0]);
  for (int i = 1; i < size; i++) {
    float diff = abs(value - arr[i]);
    if (diff < minDiff) {
      minDiff = diff;
      closest = i;
    }
  }
  return closest;
}

/**
 * @brief Shifts the array to the right or left based on the `shiftAmount`.
 * 
 * @param arr The array to shift
 * @param size The size of the array
 * @param shiftAmount The amount to shift the array
 */
void arrayShift(color* arr, int size, int shiftAmount) {
  if (shiftAmount > 0) {
    // Shift to the right
    for (int i = 0; i < shiftAmount; i++) {
      color temp = arr[size - 1];
      for (int j = size - 1; j > 0; j--) {
        arr[j] = arr[j - 1];
      }
      arr[0] = temp;
    }
  } else if (shiftAmount < 0) {
    // Shift to the left
    shiftAmount = -shiftAmount;
    for (int i = 0; i < shiftAmount; i++) {
      color temp = arr[0];
      for (int j = 0; j < size - 1; j++) {
        arr[j] = arr[j + 1];
      }
      arr[size - 1] = temp;
    }
  }
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

/**
 * @brief Prints the amount of degrees from the x-axis the lantern is tilted.
 * 
 */
void tiltAngle() {
  // motion values
  float x = lantern.motionX();
  float y = lantern.motionY();
  float z = lantern.motionZ();

  // tilt angle in radians
  float theta_x = atan2(x, sqrt(y*y + z*z));

  // convert radians to degrees
  float theta_x_deg = theta_x * 180 / M_PI;

  Serial.print("theta_x: ");
  Serial.print(theta_x_deg);
  Serial.print("\n");
}