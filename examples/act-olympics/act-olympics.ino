#include <Adafruit_CircuitPlayground.h>
#include <math.h>

#define lantern CircuitPlayground
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

void setPixels(uint8_t* pixelArr, uint8_t arrSize, uint32_t color);
float calculatePolarValue();

void setup() {
  lantern.begin();
  lantern.setBrightness(5);
}

void loop() {
  // fire();
  // fire_v3();
  // tiltLight();
  // tiltLight_v2();
  // tiltLight_v3();
  // tiltLight_v4();
  // tiltLight_v5();
  // tiltLight_v6();
  tiltLight_v7();
  // tilt();
  // tiltFireVertical();
  // lantern.clearPixels();
  // delay(500);
  // fire();
  // lantern
  // delay(1000);
}

/**
 * @brief Creates a static fire effect on the lantern
 * 
 */
void fire() {
  uint32_t orange = 0xFF5800;
  uint32_t yellow = 0xFFFF00;
  uint32_t white = 0xFFFFFF;

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
}

/**
 * @brief Creates a static fire effect on the lantern. Uses arrays to set the 
 * pixels instead of hardcoding all the values.
 * 
 */
void fire_v2() {
  uint32_t orange = 0xFF5800;
  uint32_t yellow = 0xFFFF00;
  uint32_t white = 0xFFFFFF;

  int orangeArr[] = {0,9};
  int yellowArr[] = {1,2,3,6,7,8};
  int whiteArr[]  = {4,5};

  for (uint8_t i = 0; i < sizeof(orangeArr) / sizeof(orangeArr[0]); i++) {
    lantern.setPixelColor(orangeArr[i], orange);
  }

  for (uint8_t i = 0; i < sizeof(yellowArr) / sizeof(yellowArr[0]); i++) {
    lantern.setPixelColor(yellowArr[i], yellow);
  }

  for (uint8_t i = 0; i < sizeof(whiteArr) / sizeof(whiteArr[0]); i++) {
    lantern.setPixelColor(whiteArr[i], white);
  }
}

void setPixels(uint8_t* pixelArr, uint8_t arrSize, uint32_t color) {
  for (uint8_t i = 0; i < arrSize; i++) {
    lantern.setPixelColor(pixelArr[i], color);
  }
}

/**
 * @brief Uses a helper function to adhere to DRY principles of programming to 
 * create a static fire effect on the lantern.
 * 
 */
void fire_v3() {
  uint32_t red = 0xFF0000;
  uint32_t orange = 0xFF5800;
  uint32_t yellow = 0xFFFF00;
  uint32_t white = 0xFFFFFF;

  uint8_t orangeArr[] = {0,9};
  uint8_t yellowArr[] = {1,2,3,6,7,8};
  uint8_t whiteArr[]  = {4,5};

  setPixels(orangeArr, ARRAY_SIZE(orangeArr), red);
  setPixels(yellowArr, ARRAY_SIZE(yellowArr), yellow);
  setPixels(whiteArr, ARRAY_SIZE(whiteArr), white);
}

/**
 * @brief Prints out the current values of the accelerometer
 * 
 */
void tilt() {
  delay(1000);
  Serial.print("motionX: ");
  Serial.print(lantern.motionX());
  Serial.print("\tmotionY: ");
  Serial.print(lantern.motionY());
  Serial.print("\tmotionZ: ");
  Serial.print(lantern.motionZ());
  Serial.print("\tpolar: ");
  Serial.print(calculatePolarValue());
  Serial.println();
  delay(1000);
}

/**
 * @brief Uses the tilt of the lantern basd on thresholds. No math involved.
 * 
 */
void tiltLight() {
  uint32_t green = 0x00FF00;
  uint32_t red = 0xFF0000;
  uint32_t off = 0x000000;
  int tilt_threshold = 3;

  uint8_t xPos[] = {0, 9};
  uint8_t xNeg[] = {4, 5};
  uint8_t yPos[] = {2};
  uint8_t yNeg[] = {7};
  uint8_t zPos[] = {1, 3, 6, 8};
  uint8_t zNeg[] = {1, 3, 6, 8};

  const bool xTiltPos = lantern.motionX() > tilt_threshold;
  const bool xTiltNeg = lantern.motionX() < -tilt_threshold;
  const bool yTiltPos = lantern.motionY() > tilt_threshold;
  const bool yTiltNeg = lantern.motionY() < -tilt_threshold;
  const bool zTiltPos = lantern.motionZ() > tilt_threshold;
  const bool zTiltNeg = lantern.motionZ() < -tilt_threshold;

  if (!xTiltPos && !xTiltNeg) {
    setPixels(xPos, ARRAY_SIZE(xPos), off);
    setPixels(xNeg, ARRAY_SIZE(xNeg), off);
  } else if (xTiltPos) {
    setPixels(xPos, ARRAY_SIZE(xPos), green);
    setPixels(xNeg, ARRAY_SIZE(xNeg), red);
  } else if (xTiltNeg) {
    setPixels(xNeg, ARRAY_SIZE(xNeg), green);
    setPixels(xPos, ARRAY_SIZE(xPos), red);
  }

  if (!yTiltPos && !yTiltNeg) {
    setPixels(yPos, ARRAY_SIZE(yPos), off);
    setPixels(yNeg, ARRAY_SIZE(yNeg), off);
  } else if (yTiltPos) {
    setPixels(yPos, ARRAY_SIZE(yPos), green);
    setPixels(yNeg, ARRAY_SIZE(yNeg), red);
  } else if (yTiltNeg) {
    setPixels(yNeg, ARRAY_SIZE(yNeg), green);
    setPixels(yPos, ARRAY_SIZE(yPos), red);
  }
  
  if (!zTiltPos && !zTiltNeg) {
    setPixels(zPos, ARRAY_SIZE(zPos), off);
    setPixels(zNeg, ARRAY_SIZE(zNeg), off);
  } else if (zTiltPos) {
    setPixels(zPos, ARRAY_SIZE(zPos), green);
    setPixels(zNeg, ARRAY_SIZE(zNeg), off);
  } else if (zTiltNeg) {
    setPixels(zNeg, ARRAY_SIZE(zNeg), red);
    setPixels(zPos, ARRAY_SIZE(zPos), off);
  }
}

/**
 * @brief Calculates the angle of tilt in the x and y direction
 * 
 */
void tiltLight_v2() {
  // motion values
  float x = lantern.motionX();
  float y = lantern.motionY();
  float z = lantern.motionZ();

  // tilt angle
  float theta_x = atan2(x, sqrt(y*y + z*z));
  float theta_y = atan2(y, sqrt(x*x + z*z));

  // Convert angles to degrees
  float theta_x_deg = theta_x * 180 / M_PI;
  float theta_y_deg = theta_y * 180 / M_PI;

  // Determine the closest pixel
  int pixel_index_x = round((theta_x_deg + 180) / 36) % 10;
  int pixel_index_y = round((theta_y_deg + 180) / 36) % 10;
  // this grabs the highest pixel number depending on which side is closest
  // ie. if the x tilt is at a positive angle then the highest pixel number is 9
  // ie .if the x tilt is at a negative angle then the highest pixel number is 3

  
  // Set every pixel besides the closest pixel to off
  for (int i = 0; i < 10; i++) {
    lantern.setPixelColor(i, 0x000000);
  }

  // tilt direction
  if (theta_x > 0) {
    lantern.setPixelColor(0, 0xFF0000);
    lantern.setPixelColor(9, 0xFF0000);
  } else {
    lantern.setPixelColor(4, 0xFF0000);
    lantern.setPixelColor(5, 0xFF0000);
  }

  if (theta_y > 0) {
    lantern.setPixelColor(2, 0xFF0000);
  } else {
    lantern.setPixelColor(7, 0xFF0000);
  }
  
}

/**
 * @brief Uses polar coordinates to determine the tilt of the lantern and 
 * displays a single pixel the direction closest to the sky.
 * 
 */
void tiltLight_v3() {
  const float x = lantern.motionX();
  const float y = lantern.motionY();
  const float z = lantern.motionZ();
  const uint32_t red = 0xFF0000;
  const uint32_t off = 0x000000;
  const int num_pixels = 10;

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
  const float thresold = 0.3;

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
 * @brief Uses polar coordaintes to determine the tilt of the lantern and
 * shifts the pattern to the left or right based on the tilt.
 * 
 */
void tiltLight_v4() {
  const float x = lantern.motionX();
  const float y = lantern.motionY();
  const float z = lantern.motionZ();
  const int num_pixels = 10;
  const uint32_t red    = 0xFF0000;
  const uint32_t orange = 0xFF5800;
  const uint32_t yellow = 0xFFFF00;
  const uint32_t white  = 0xFFFFFF;
  const uint32_t off    = 0x000000;

  const float theta = atan2(y, x);
  // to determine the opposite direction (like the ground), we can inverse the 
  // radians by swapping the left and right half of the array.
  const float radians[num_pixels] = {
      M_PI*1/6,   M_PI*2/6,   M_PI*3/6,   M_PI*4/6,   M_PI*5/6, // Left half
    0-M_PI*5/6, 0-M_PI*4/6, 0-M_PI*3/6, 0-M_PI*2/6, 0-M_PI*1/6  // Right half
  };
  float difference[num_pixels] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  const float pattern[num_pixels] = {
    red, orange, orange, yellow, white, white, yellow, orange, orange, red
  }
  // to increase the amount of pixels that are lit up, we can increase the
  // threshold value. 
  //    0.3 = 1 pixel
  //    0.7 = 2-3 pixels
  const float thresold = 0.3;
  const float shiftAmount = findClosest(radians, num_pixels, theta);

  // assigns colors based on the array shift patterns
  for (int i = 0; i < num_pixels; i++) {
    const float diff = abs(theta - radians[i]);
    difference[i] = diff;
    if (diff <= thresold) {
      lantern.setPixelColor(i, pattern[(i + shiftAmount) % num_pixels]);
    } else {
      lantern.setPixelColor(i, off);
    }
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
 * @brief Uses polar coordinates to determine the tilt of the lantern and 
 * displays a pixel for the sky and a for the ground.
 * 
 */
void tiltLight_v5() {
  float x = lantern.motionX();
  float y = lantern.motionY();
  float z = lantern.motionZ();

  float theta = atan2(y, x);
  // original radians for sky pointer
  float radiansSky[10] = {
      M_PI*1/6,   M_PI*2/6,   M_PI*3/6,   M_PI*4/6,   M_PI*5/6,           // Left half
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
    if (diffSky <= 0.3) {
      lantern.setPixelColor(i, 0xFF0000);
    } else {
      lantern.setPixelColor(i, 0x000000);
    }
    if (diffGnd <= 0.3) {
      lantern.setPixelColor(i, 0x00FF00);
    } else {
      lantern.setPixelColor(i, 0x000000);
    }
  }
}

/**
 * @brief Uses polar coordinates to determine the tilt of the lantern and
 * splits the lantern into 3 categories: sky, ground, and in between. The sky
 * will have red, the ground will have green, and the in between will have no 
 * color.
 * 
 */
void tiltLight_v6() {
  float x = lantern.motionX();
  float y = lantern.motionY();
  float z = lantern.motionZ();

  float theta = atan2(y, x);
  // original radians for sky pointer
  float radiansSky[10] = {
      M_PI*1/6,   M_PI*2/6,   M_PI*3/6,   M_PI*4/6,   M_PI*5/6,           // Left half
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
      lantern.setPixelColor(i, 0xFF0000);
    } else {
      lantern.setPixelColor(i, 0x000000);
    }
    if (diffGnd <= 0.7) {
      lantern.setPixelColor(i, 0x00FF00);
    } else {
      lantern.setPixelColor(i, 0x000000);
    }
  }
}

/**
 * @brief Uses polar coordinates to determine the tilt of the lantern and
 * splits the lantern into 3 categories: sky, ground, and in between. The sky
 * will have red, the ground will have green, and the in between will have blue.
 * 
 */
void tiltLight_v7() {
  float x = lantern.motionX();
  float y = lantern.motionY();
  float z = lantern.motionZ();

  float theta = atan2(y, x);
  // original radians for sky pointer
  float radiansSky[10] = {
      M_PI*1/6,   M_PI*2/6,   M_PI*3/6,   M_PI*4/6,   M_PI*5/6,           // Left half
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
      lantern.setPixelColor(i, 0xFF0000);
    }
    if (diffGnd <= 0.7) {
      lantern.setPixelColor(i, 0x00FF00);
    } 
    if (diffSky > 0.7 && diffGnd > 0.7) {
      lantern.setPixelColor(i, 0x0000FF);
    }
  }
}

/**
 * @brief Uses polar coordiantes to determine the tilt of the lantern and 
 * uses some randomness to add flickering add to the torch effect.
 * 
 */
void tiltLight_v8() {

}

/**
 * @brief Uses perlin noise to apply a flickering effect to the lantern.
 * 
 */
void flicker() {

}

/**
 * @brief Implements perlin noise. Smoothed randomness function.
 * https://youtu.be/8ZEMLCnn8v0?si=XWf2icArjqzSchd0
 * 
 */
void perlinNoise() {

}

void assignPixels(uint32_t* colors) {
  uint8_t pixel_count = 10;
  for (uint8_t i = 0; i < pixel_count; i++) {
    lantern.setPixelColor(i, colors[i]);
  }
}

void tiltFire() {
  uint32_t coolHeat = 0xFF0000; // Red, representing cooler flames at the top
  uint32_t warmHeat = 0xFF5800; // Orange, representing warm flames
  uint32_t hotHeat = 0xFFFF00;  // Yellow, representing hot flames
  uint32_t peakHeat = 0xFFFFFF; // White, representing the peak heat at the bottom
  uint32_t off = 0x000000;      // Off, representing no heat

  // initial values
  uint32_t colors[10] = {off, off, off, off, off, off, off, off, off, off};
  const int coolThreshold = 1;
  const int warmThreshold = 2;
  const int hotThreshold = 3;
  float radians[10] = {
    M_PI*1/6, M_PI*2/6, M_PI*3/6, M_PI*4/6, M_PI*5/6,           // Left half
    0-M_PI*5/6, 0-M_PI*4/6, 0-M_PI*3/6, 0-M_PI*2/6, 0-M_PI*1/6  // Right half
    // M_PI*6/6, M_PI*7/6, M_PI*8/6, M_PI*9/6, M_PI*10/6           // Right half
  };
  float difference[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  float theta = abs(calculatePolarValue());
  // assign colors based on difference between theta and radians
  for (int i = 0; i < 10; i++) {
    float diff = abs(theta - radians[i]);
    difference[i] = diff;
    if (diff <= coolThreshold) {
      colors[i] = coolHeat;
    } else if (diff <= warmThreshold) {
      colors[i] = warmHeat;
    } else if (diff <= hotThreshold) {
      colors[i] = hotHeat;
    } else {
      colors[i] = peakHeat;
    }
  }
  Serial.print("Theta: ");
  Serial.print(theta);
  // Serial.print("\t");
  // printArray(difference, 10);
  Serial.print("Radian: ");
  printArray(radians, 10);
  Serial.println();
  assignPixels(colors);
}

void printArray(float* arr, uint8_t size) {
  for (uint8_t i = 0; i < size; i++) {
    Serial.print(arr[i]);
    Serial.print(" ");
  }
  Serial.println();
}

void calculateTopAxis(int x, int y, int z, uint8_t& topAxis1, uint8_t& topAxis2) {
  int diffXY = abs(x - y);
  int diffXZ = abs(x - z);
  int diffYZ = abs(y - z);

  if (diffXY <= diffXZ && diffXY <= diffYZ) {
    topAxis1 = 0; // X-axis
    topAxis2 = 1; // Y-axis
  } else if (diffXZ <= diffXY && diffXZ <= diffYZ) {
    topAxis1 = 0; // X-axis
    topAxis2 = 2; // Z-axis
  } else {
    topAxis1 = 1; // Y-axis
    topAxis2 = 2; // Z-axis
  }
}

// TODO: conver this to a library function
void arrayShift(int* arr, int size, int shiftAmount, bool shiftLeft) {
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

float convertToPolar(float x, float y) {
  return atan2(y, x);
}

float calculatePolarValue() {
  float x = lantern.motionX();
  float y = lantern.motionY();
  float polarValue = convertToPolar(x, y);
  return polarValue;
}

void findMaxAxis() {
  
  const int maxAxis = max(lantern.motionX(), max(lantern.motionY(), lantern.motionZ()));
  // Axis X = 0
  // Axis Y = 1
  // Axis Z = 2
  uint8_t topAxis = 0;

  if (maxAxis == lantern.motionX()) {
    topAxis = 0;
  } else if (maxAxis == lantern.motionY()) {
    topAxis = 1;
  } else if (maxAxis == lantern.motionZ()) {
    topAxis = 2;
  }
}

void pendulum() {
  // int pos = 0;
  // float increment = 2 * M_PI / 10;
  // MomentumH = 0;
  // MomentumV = 0;

  // const float friction = 0.99;
  // const float swing = 10;
  // const float gravity = 50;
  // const halfWidth = 1.25;

  // TorqueH = cos(pos * increment);
  // TorqueV = sin(pos * increment);

  // MomentumH += TorqueH * motionX() / swing;
  // MomentumV += TorqueV * motionY() / swing;

  // MomentumH *= friction;
  // MomentumV *= friction;

  // pos += MomentumH + MomentumV;
}