#include <Arduino.h>

#define PI 3.14159265358979323846

/**
 * The function calculates the value of a Gaussian distribution at a given position.
 * 
 * @param _radiant The _radiant parameter represents the input value for which you want to calculate
 * the value of the Gaussian distribution function.
 * @param height The height parameter represents the maximum value of the Gaussian distribution curve.
 * It determines the peak value of the curve.
 * @param position The position parameter represents the center of the Gaussian distribution. It
 * determines where the peak of the distribution will be located.
 * @param length The "length" parameter in the given function represents the standard deviation of the
 * Gaussian distribution. It determines the width of the curve. A larger value of "length" will result
 * in a wider curve, while a smaller value will result in a narrower curve.
 * 
 * @return the value of the Gaussian (normal) distribution function, which is calculated using the
 * given parameters.
 */
double gaussian(double _radiant, double height, double position, double length) {
  // Gaussian (normal) distribution function
  return height * exp(-(pow((_radiant - position), 2) / (2 * pow(length, 2))));
}

/**
 * The function calculates the red value for a sun based on the radiant input.
 * 
 * @param _radiant The _radiant parameter represents the radiant energy received from the sun.
 * 
 * @return the result of the expression `gaussian(_radiant, 250, PI, 0.7) + random(10)`.
 */
int getRed4Sun(double _radiant) {

  //return 0;
  return gaussian(_radiant, 250, PI, 0.7) + random(10);

}

/**
 * The function calculates the amount of green light emitted by the sun based on the input radiant
 * value.
 * 
 * @param _radiant The _radiant parameter represents the amount of radiant energy received from the
 * sun.
 * 
 * @return the result of the expression `gaussian(_radiant, 200, PI, 0.5) + random(10)`.
 */
int getGreen4Sun(double _radiant) {

  //return 0; 
  return gaussian(_radiant, 200, PI, 0.5) + random(10);

}

/**
 * The function "getGreen4Sky" returns the result of applying a Gaussian function to the input radiant
 * value.
 * 
 * @param _radiant The _radiant parameter is the input value used to calculate the green value for the
 * sky.
 * 
 * @return the result of the `gaussian` function with the given parameters `_radiant`, 100, PI, and
 * 0.5.
 */
int getGreen4Sky(double _radiant) {

  //return 0; 
  return gaussian(_radiant, 80,  PI, 0.5);

}

/**
 * The function calculates the amount of blue in the sky based on the input radiant value.
 * 
 * @param _radiant The parameter `_radiant` is the radiant value of the sky. It is used as input to
 * calculate the blue color intensity for the sky.
 * 
 * @return the result of the expression `gaussian(_radiant, 140, PI, 0.7) + 10`.
 */
int getBlue4Sky(double _radiant) {
    
    //return 0;
    return gaussian(_radiant, 140, PI, 0.7) + 10;
}

/**
 * The function "getRed4Sky" returns the result of applying a Gaussian function to the input radiant
 * value.
 * 
 * @param _radiant The _radiant parameter is the input value used to calculate the red value for the
 * sky.
 * 
 * @return the result of the `gaussian` function with the given parameters `_radiant`, 100, PI, and
 * 0.5.
 */
int getRed4Sky(double _radiant) {

  return 0; 
  //return gaussian(_radiant, 250,  PI, 0.5);

}



int getRedFire() {
    return 200;
}

int getGreenFire() {
    return 90;
}

int GetRedFireFlame() {
    return 250;
}

int GetGreenFireFlame() {
    return 80 + random(175);
}