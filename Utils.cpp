
#include "Utils.h"
#include <Adafruit_CircuitPlayground.h>
#include <math.h>

#define lantern CircuitPlayground
#define color uint32_t

void Utils::setPixels(uint8_t* pixelArr, uint8_t arrSize, uint32_t color) {
  for (uint8_t i = 0; i < arrSize; i++) {
      lantern.setPixelColor(pixelArr[i], color);
  }
}

void Utils::arrayShift(int* arr, int size, int shiftAmount, bool shiftLeft) {
  if (shiftLeft) {
      for (int i = 0; i < shiftAmount; i++) {
        int temp = arr[0];
        for (int j = 0; j < size - 1; j++) {
          arr[j] = arr[j + 1];
        }
        arr[size - 1] = temp;
      }
    } else {
    for (int i = 0; i < shiftAmount; i++) {
      int temp = arr[size - 1];
      for (int j = size - 1; j > 0; j--) {
        arr[j] = arr[j - 1];
      }
      arr[0] = temp;
    }
  }
}


int Utils::findMaxAxis() {
  const int maxAxis = max(lantern.motionX(), max(lantern.motionY(), lantern.motionZ()));
  // Axis X = 0
  // Axis Y = 1
  // Axis Z = 2
  int topAxis = 0;

  if (maxAxis == lantern.motionX()) {
    topAxis = 0;
  } else if (maxAxis == lantern.motionY()) {
    topAxis = 1;
  } else if (maxAxis == lantern.motionZ()) {
    topAxis = 2;
  }
  return topAxis;
}

float Utils::calculatePolarValue() {
  float x = lantern.motionX();
  float y = lantern.motionY();
  float polarValue = atan2(y, x);
  return polarValue;
}

void Utils::printArray(float* arr, uint8_t size) {
  for (uint8_t i = 0; i < size; i++) {
    Serial.print(arr[i]);
    Serial.print(" ");
  }
  Serial.println();
}

int Utils::arraySize(int* arr) {
  return sizeof(arr) / sizeof(arr[0]);
}

int Utils::findClosest(float* arr, int size, float value) {
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