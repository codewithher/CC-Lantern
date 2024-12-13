///////////////////////////////////////////////////////////////////////////////
// PART 1: Imports / Globals  /////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#include <Adafruit_CircuitPlayground.h>
#include <math.h>

#define lantern CircuitPlayground
#define arraySize(x) (sizeof(x) / sizeof((x)[0]))

using color = uint32_t;
using byte = uint8_t;

color red = 0xFF0000;
color orange = 0xFF5800;
color yellow = 0xFFFF00;
color white = 0xFFFFFF;

///////////////////////////////////////////////////////////////////////////////
// PART 2: Setup and Loop /////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(9600);
  lantern.begin();
  lantern.setBrightness(5);
}

void loop() {
  fire();
  fire_array();
  fire_loading();
  fire_spin();
}

///////////////////////////////////////////////////////////////////////////////
// PART 3: Functions  /////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Creates a static fire effect on the lantern
 * 
 */
void fire() {
  lantern.setPixelColor(0, orange);
  lantern.setPixelColor(9, orange);
  
  lantern.setPixelColor(1, yellow);
  lantern.setPixelColor(2, yellow);
  lantern.setPixelColor(3, yellow);
  lantern.setPixelColor(6, yellow);
  lantern.setPixelColor(7, yellow);
  lantern.setPixelColor(8, yellow);

  lantern.setPixelColor(4, white);
  lantern.setPixelColor(5, white);

  delay(1000);
  lantern.clearPixels();
}

/**
 * @brief Creates a static fire effect on the lantern. Uses arrays to set the 
 * pixels instead of hardcoding all the values.
 * 
 */
void fire_array() {
  color colors[] = {
    red, orange, yellow, yellow, white, 
    white, yellow, yellow, orange, red
  };

  // Use this to assign the colors of the array to the pixels on the lantern.
  setPixelColors(colors);

  delay(1000);
  lantern.clearPixels();
}

/**
 * @brief Creates a fire effect on the lantern that loads in a circle.
 * 
 */
void fire_loading() {
  color colors[] = {
    red, orange, yellow, yellow, white, 
    white, yellow, yellow, orange, red
  };

  // Manually set each pixel color in the array then wait 100ms
  // for (starting value; condition; step size)
  for (int i = 0; i < arraySize(colors); i++) {
    lantern.setPixelColor(i, colors[i]);
    delay(100);
  }

  delay(1000);
  lantern.clearPixels();
}

/**
 * @brief Creates a fire effect on the lantern that spins in a circle.
 * 
 */
void fire_spin() {
  color colors[] = {
    red, orange, yellow, yellow, white, 
    white, yellow, yellow, orange, red
  };
  int num_spins = 10;

  for (int i = 0; i < num_spins; i++) {
    printArray(colors, arraySize(colors));
    setPixelColors(colors);
    arrayShift(colors, arraySize(colors), 1);
    delay(100);
  }

  delay(1000);
  lantern.clearPixels();
}

///////////////////////////////////////////////////////////////////////////////
// PART 4: Helper Functions ///////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Prints the contents of the color array
 * 
 * @param arr The array to print
 */
void printArray(color* arr, int size) {
  for (int i = 0; i < size; i++) {
    int hexValue = arr[i];
    // Ensure printing of leading zeros
    Serial.print(hexValue, HEX); // Using HEX to print the color values in hexadecimal
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
