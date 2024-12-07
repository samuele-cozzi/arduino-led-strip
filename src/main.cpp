#include <Arduino.h>
#include <FastLED.h>
#include "utils/sky-math.h"

// For led chips like WS2812, which have a data line, ground, and power, you just
// need to define DATA_PIN.
#define DATA_PIN_HOUSE 3
#define DATA_PIN_GARDEN 4

// How many leds in your strip?
// Define the array of leds
#define NUM_LEDS 60 //60
CRGB leds_house[NUM_LEDS];
CRGB leds_garden[NUM_LEDS];


double time = 0.0;                // Initial value between 0 and 672 (24 hours, 7 days, 4 seasons)
double hour_duration_sec = 4;     // hour duration in led strip in seconds
double hour_day_loops = 10;       // number of loops in one hour during day
double hour_night_loops = 100;    // number of loops in one hour during day


/**
 * The setup function initializes the serial communication and adds the LED strip configuration.
 */
void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812B, DATA_PIN_HOUSE, RGB>(leds_house, NUM_LEDS); // GRB ordering is typical

  FastLED.addLeds<WS2812B, DATA_PIN_GARDEN, RGB>(leds_garden, NUM_LEDS); // GRB ordering is typical
}

/**
 * The `loop` function simulates the passage of time by incrementing the `time` variable based on
 * whether it is night or day, sets the color of each LED in a LED strip based on the current time and
 * LED position, and delays the program execution to simulate the passage of time.
 */
void loop() {
  //Serial.println("start:" + String(time));

  /* This code is checking if it is night time or day time based on the value of the variable
  `_isNight`. If it is night time, it increments the `time` variable by `1 / hour_night_loops`,
  otherwise it increments it by `1 / hour_day_loops`. This is used to simulate the passage of time
  in the program. */
  bool _isNight = isNight(time);
  if (_isNight) {
    time += (1 / hour_night_loops);
  }
  else {
    time += (1 / hour_day_loops);
  }
  
  // Ensure the variable stays between 0 and 672
  if (time > 672) {
    time = 0.0;
  }

  /* The code is looping through each LED in the LED strip and setting its color based on the current
  time (`time` variable) and its position in the strip (`i`). The `getSkyColor` function is called
  with the current time, LED position, and total number of LEDs as arguments to calculate the
  appropriate color for that LED. The calculated color is then assigned to the corresponding element
  in the `leds` array. */
  for (int i = 0; i < NUM_LEDS; i++) {
    leds_house[i] = getSkyColor(time, i, NUM_LEDS);
  }

  for (int i = 0; i < NUM_LEDS; i++) {
    leds_garden[i] = getGardenColor(time, i, NUM_LEDS);
  }

  FastLED.show();

  
  /* The code is checking if it is night time or day time based on the value of the variable
  `_isNight`. If it is night time, it delays the program execution for a duration calculated as
  `hour_duration_sec * 1000 / hour_night_loops`. If it is day time, it delays the program execution
  for a duration calculated as `hour_duration_sec * 1000 / hour_day_loops`. This delay is used to
  simulate the passage of time in the program. */
  _isNight = isNight(time);
  if (_isNight) {
    delay(hour_duration_sec * 1000 / hour_night_loops);
  }
  else {
    delay(hour_duration_sec * 1000 / hour_day_loops);
  }

  //Serial.println("end");
}

