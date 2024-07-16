#ifndef Utils_h
#define Utils_h

class Utils {
  public:
    void setPixels(uint8_t* pixelArr, uint8_t arrSize, uint32_t color);
    void arrayShift(int* arr, int size, int shiftAmount, bool shiftLeft);
    int findMaxAxis(float* arr, int size, float value);
    float calculatePolarValue();
    void printArray(float* arr, uint8_t size);
    int arraySize(int* arr);
    
    /**
     * @brief Finds the closest value in an array to a specified value.
     * 
     * @param arr 
     * @param size 
     * @param value 
     * @return int 
     */
    int findClosest(float* arr, int size, float value) {
};

#endif