#include <Arduino.h>
#include <FastLED.h>
#include "utils/sky-math.h"

// For led chips like WS2812, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
// Clock pin only needed for SPI based chipsets when not using hardware SPI
#define DATA_PIN 3

// How many leds in your strip?
#define NUM_LEDS 60 //60

// Define the array of leds
CRGB leds[NUM_LEDS];


double time = 0.0;                // Initial value between 0 and 672 (24 hours, 7 days, 4 seasons)
double hour_duration_sec = 1;     // in seconds
double hour_day_loops = 10;        // # di loop in one hour during day
double hour_night_loops = 100;     // # di loop in one hour during day


void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS); // GRB ordering is typical
}

void loop() {
  //Serial.println("start:" + String(time));

  bool _isNight = isNight(time);
  if (_isNight) {
    time += (1 / hour_night_loops);
  }
  else {
    time += (1 / hour_day_loops);
  }
  
  // Ensure the variable stays between 0 and 1
  if (time > 672) {
    time = 0.0;
  }

  for (int i = 0; i < NUM_LEDS; i++) {
    // Turn the LED on, then pause
    //leds[0] = CRGB::Red;
    leds[i] = getSkyColor(time, i, NUM_LEDS);
  }

  FastLED.show();

  // calculate delay
  _isNight = isNight(time);
  if (_isNight) {
    delay(hour_duration_sec * 1000 / hour_night_loops);
  }
  else {
    delay(hour_duration_sec * 1000 / hour_day_loops);
  }

  //Serial.println("end");
}

