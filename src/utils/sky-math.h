#include <Arduino.h>
#include <FastLED.h>
#include "day-night-colors.h"

#define NUM_FIRES 2
int fires[NUM_FIRES] = {54, 48};

/**
 * The function calculates the radiant angle based on the given time.
 * 
 * @param _time The _time parameter represents the time in hours.
 * 
 * @return the radiant value calculated from the given time.
 */
double getRadiantFromTime(double _time) {
  double _radiant = (2 * PI / 24) * _time;
  double cycle = floor(_radiant / (2 * PI));

  return _radiant - (cycle * 2 * PI);
}

/**
 * The function "isNight" determines if a given time is during the night based on the calculated
 * radiant value.
 * 
 * @param _time The parameter `_time` represents the time of the day in hours.
 * 
 * @return a boolean value, either true or false.
 */
bool isNight(double _time) {
  double radiant = getRadiantFromTime(_time);
  if(radiant < (7 * PI / 20) || radiant > (33 * PI / 20)) {
    return true;
  }
  else
  {
    return false;
  }
}

/**
 * The function calculates the longitude of the sun based on the given radiant and total.
 * 
 * @param _radiant The _radiant parameter represents the angle in radians (possible value from 0 to 2 * PI).
 * @param _tot The total number of degrees in a circle.
 * 
 * @return the result of the expression ceil((_tot / (2 * PI)) * _radiant).
 */
int getSunLong(double _time, int _tot) {
  double _radiant = getRadiantFromTime(_time);

  return ceil((10 * pow((_radiant - PI), 2)) + 10);
}

/**
 * The function calculates the sun dispersion based on the sun log and total number of logs.
 * 
 * @param sun_log The sun_log parameter represents the logarithm of the intensity of sunlight.
 * @param _tot The parameter "_tot" represents the total number of data points or observations.
 * 
 * @return a double value.
 */
double getSunDispersion(int sun_log, int _tot){
  //return 5;
  return (pow((sun_log - (_tot / 2)), 2) / (_tot / 2)) + 1;
}

/**
 * The function `getSkyColor` returns a CRGB color value based on the time, longitude, and total number
 * of locations.
 * 
 * @param _time The _time parameter represents the current time. It is a double value that can be used
 * to calculate the position of the sun and determine the color of the sky.
 * @param _long The parameter `_long` represents the longitude of a specific location.
 * @param _tot The parameter "_tot" represents the total number of divisions in the sky. It is used in
 * calculations to determine the position of the sun and the dispersion of its light.
 * 
 * @return a CRGB object, which represents a color in the RGB color model.
 */

CRGB getSkyColor(double _time, int _long, int _tot) {

  double radiant = getRadiantFromTime(_time);
  int sun_long = getSunLong(_time, _tot);
  double sun_dispersion = getSunDispersion(sun_long, _tot);

  int red = 0;
  int green = 0;
  int blue = 0;

  if (isNight(_time)){
    blue = min(getBlue4Sky(radiant),250);

    for (int j = 0; j < NUM_FIRES; j++) {
      if (fires[j] == _long){
        red = getRedFire();
        green = getGreenFire();
      } else if (_long >= fires[j] - 1 && _long <= fires[j] + 2){
        red = GetRedFireFlame();
        green = GetGreenFireFlame();
      }
    }
  }
  else
  {
      if (_long >= sun_long - sun_dispersion && _long <= sun_long + sun_dispersion){
        // Sun Colors
        red = min(getRed4Sun(radiant),250);
        green = min(getGreen4Sky(radiant) + getGreen4Sun(radiant),250);
        blue = min(getBlue4Sky(radiant),250);
      }
      else
      {
        // Sky Colors
        red = min(0,250);
        green = min(getGreen4Sky(radiant),250);
        blue = min(getBlue4Sky(radiant), 250);
      }
  }

  //Serial.println("Current Value R-" + String(red) + "-G-" + String(green) + "-B-" + String(blue) + "-");

  return CRGB(green,red,blue);
}