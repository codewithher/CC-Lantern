#ifndef Utils_h
#define Utils_h

class Utils {
  public:
  /**
   * @brief Set all the pixels to the specified color.
   * 
   * @param pixelArr 
   * @param arrSize 
   * @param color 
   */
    void setPixels(uint8_t* pixelArr, uint8_t arrSize, uint32_t color);

    /**
     * @brief Rotates the array by a specified amount.
     * 
     * @param arr 
     * @param size 
     * @param shiftAmount 
     * @param shiftLeft 
     */
    void arrayShift(int* arr, int size, int shiftAmount, bool shiftLeft);
    
    /**
     * @brief Find the max axis of the accelerometer.
     * 
     * @param arr 
     * @param size 
     * @param value 
     * @return int 
     */
    int findMaxAxis(float* arr, int size, float value);
    
    /**
     * @brief Calculates the polar value of the x and y axis.
     * 
     * @return float 
     */
    float calculatePolarValue();

    /**
     * @brief Prints the contents of an array.
     * 
     * @param arr 
     * @param size 
     */
    void printArray(float* arr, uint8_t size);

    /**
     * @brief Calculates the size of the array.
     * 
     * @param arr 
     * @return int 
     */
    int arraySize(int* arr);

    /**
     * @brief Finds the closest value in an array to a specified value.
     * 
     * @param arr 
     * @param size 
     * @param value 
     * @return int 
     */
    int findClosest(float* arr, int size, float value);
};

#endif