#include <Arduino.h>
#include <FastLED.h>

#define PI 3.14159265358979323846

#define NUM_FIRES 2
int fires[NUM_FIRES] = {5, 20};

double getRadiantFromTime(double _time) {
  double _radiant = (2 * PI / 24) * _time;
  double cycle = floor(_radiant / (2 * PI));

  return _radiant - (cycle * 2 * PI);
}

int getSunLong(double _radiant, int _tot) {
  return ceil((_tot / (2 * PI)) * _radiant);
}

double getSunDispersion(int sun_log, int _tot){
  return (pow((sun_log - (_tot / 2)), 2) / (_tot / 2)) + 1;
}

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

double gaussian(double _radiant, double height, double position, double length) {
  // Gaussian (normal) distribution function
  return height * exp(-(pow((_radiant - position), 2) / (2 * pow(length, 2))));
}

int getRed4Sun(double _radiant) {

  //return 0;
  return gaussian(_radiant, 250, PI, 0.7) + random(10);

}

int getGreen4Sun(double _radiant) {

  //return 0; 
  return gaussian(_radiant, 200, PI, 0.5) + random(10);

}

int getGreen4Sky(double _radiant) {

  //return 0; 
  return gaussian(_radiant, 100,  PI, 0.5);

}

int getBlue4Sky(double _radiant) {
    
    //return 0;
    return gaussian(_radiant, 140, PI, 0.7) + 10;
}



CRGB getSkyColor(double _time, int _long, int _tot) {

  double radiant = getRadiantFromTime(_time);
  int sun_long = getSunLong(radiant, _tot);
  double sun_dispersion = getSunDispersion(sun_long, _tot);

  int red = 0;
  int green = 0;
  int blue = 0;

  if (isNight(_time)){
    blue = min(getBlue4Sky(radiant),250);

    for (int j = 0; j < NUM_FIRES; j++) {
      if (fires[j] == _long){
        red = 200;
        green = 90;
      } else if (_long >= fires[j] - 1 && _long <= fires[j] + 2){
        red = 255;
        green = 80 + random(175);
      }
    }
  }
  else
  {
      if (_long >= sun_long - sun_dispersion && _long <= sun_long + sun_dispersion){
        // with sun
        red = min(getRed4Sun(radiant),250);
        green = min(getGreen4Sky(radiant) + getGreen4Sun(radiant),250);
        blue = min(getBlue4Sky(radiant),250);
      }
      else
      {
        // without sun
        red = min(0,250);
        green = min(getGreen4Sky(radiant),250);
        blue = min(getBlue4Sky(radiant), 250);
      }
  }

  //Serial.println("Current Value R-" + String(red) + "-G-" + String(green) + "-B-" + String(blue) + "-");

  return CRGB(green,red,blue);
}