#include "sensor.h"
#include <Arduino.h>

#define SENSOR_PIN A0

// Max factory temperature 379F/193C.
// 379F/193C is about 718 w/ 10K resistor from sensor to ground.

namespace Sensor {
  int raw;
  float temp;

  // TODO: Read/write these values to/from EEPROM.
  // TODO: Allow calibration through menu.
  float cal[2][2] = {{76, 20.4}, {718, 193}};
  float m = (cal[1][1] - cal[0][1]) / (cal[1][0] - cal[0][0]);
  float b = cal[0][1] - m * cal[0][0];

  void setup() {
    pinMode(SENSOR_PIN, INPUT);
  }

  void update() {
    raw = analogRead(SENSOR_PIN);
    temp = m * raw + b;
  }
}
