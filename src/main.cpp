#include <Arduino.h>
#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 10 //60

// For led chips like WS2812, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
// Clock pin only needed for SPI based chipsets when not using hardware SPI
#define DATA_PIN 3
#define PI 3.14159265358979323846

// Define the array of leds
CRGB leds[NUM_LEDS];

double time = 0.0; // Initial value between 0 and 672
int delay_unit = 1000;
int day_interval = 1;
int night_interval = 100;

double getRadiantFromTime(double _time) {
  double _radiant = (2 * PI / 24) * _time;
  double cycle = floor(_radiant / (2 * PI));

  return _radiant - (cycle * 2 * PI);
}

int getSunLong(double _radiant) {
  return ceil((NUM_LEDS / (2 * PI)) * _radiant);
}

bool isNight(double _time) {
  return false;
}

double gaussian(double _radiant, double height, double position, double length) {
  // Gaussian (normal) distribution function
  return height * exp(-(pow((_radiant - position), 2) / (2 * pow(length, 2))));
}

int getRed4Sun(double _radiant) {

  //return 0;

  double cycle = floor(_radiant / (2 * PI));
  return gaussian(_radiant, 250, (cycle * 2 * PI) + (PI), 0.7);

  // This function takes an angle in radians (x) and returns the maximum between sin(x) and 0.
  // double cycle = floor(_radiant / (2 * PI));
  // double gaussian1 = gaussian(_radiant, 230, (cycle * 2 * PI) + (PI / 16), 0.1);
  // double gaussian2 = gaussian(_radiant, 230, (cycle * 2 * PI) + (15 * PI / 16), 0.1);

  // return gaussian1 + gaussian2;

}

int getGreen4Sun(double _radiant) {

  //return 0; 

  double cycle = floor(_radiant / (2 * PI));
  return gaussian(_radiant, 200, (cycle * 2 * PI) + (PI), 0.5);

}

int getGreen4Sky(double _radiant) {

  //return 0; 

  double cycle = floor(_radiant / (2 * PI));
  return gaussian(_radiant, 100, (cycle * 2 * PI) + (PI), 0.5);

}

int getBlue4Sky(double _radiant) {
    
    //return 0;

    double cycle = floor(_radiant / (2 * PI));
    return gaussian(_radiant, 140, (cycle * 2 * PI) + (PI), 0.7) + 10;

    // This function takes an angle in radians (x) and returns the maximum between sin(x) and 0.
    // int shift = 50;
    // return max(static_cast<int>(((150 - shift) * sin(_radiant)) + shift), 0);
}

CRGB getSkyColor(double _time, int _long) {

  double radiant = getRadiantFromTime(_time);
  int sun_long = getSunLong(radiant);

  int red = 0;
  int green = 0;
  int blue = 0;



  if (_long >= sun_long - 1 && _long <= sun_long + 1){
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

  Serial.println("Current Value R-" + String(red) + "-G-" + String(green) + "-B-" + String(blue) + "-");

  return CRGB(green,red,blue);
}

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS); // GRB ordering is typical
}

void loop() {
  Serial.println("start");

  // time 
  // - 24 ore
  // - 7 giorni
  // - 4 stagioni
  // tot: 672

  bool _isNight = isNight(time);
  if (_isNight) {
    time += 1.0 / night_interval;
  }
  else {
    time += 1.0 / day_interval;
  }
  
  // Ensure the variable stays between 0 and 1
  if (time > 672) {
    time = 0.0;
  }

  for (int i = 0; i < NUM_LEDS; i++) {
    // Turn the LED on, then pause
    //leds[0] = CRGB::Red;
    leds[i] = getSkyColor(time,i);
  }

  FastLED.show();

  // calculate delay
  _isNight = isNight(time);
  if (_isNight) {
    delay(delay_unit / night_interval);
  }
  else {
    delay(delay_unit / day_interval);
  }

  Serial.println("end");
}

