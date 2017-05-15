#include "sensor.h"
#include <Arduino.h>

#define SENSOR_PIN A0
#define SENSOR_UPDATE 1000

// Max factory temperature 379F/193C.
// 379F/193C is about 738 w/ 10K resistor from sensor to ground.

namespace Sensor {
  int raw;
  int last_raw = -1;
  double temp;

  unsigned long current_millis;
  unsigned long next_update_millis = 0;

  // TODO: Read/write these values to/from EEPROM.
  // TODO: Allow calibration through menu.
  float cal[2][2] = {{76, 20.4}, {738, 193}};
  float m = (cal[1][1] - cal[0][1]) / (cal[1][0] - cal[0][0]);
  float b = cal[0][1] - m * cal[0][0];

  void setup() {
    pinMode(SENSOR_PIN, INPUT);
  }

  void loop() {
    raw = 30;
    current_millis = millis();

    if (current_millis >= next_update_millis) {
      update();
      next_update_millis = current_millis + SENSOR_UPDATE;
    }
  }

  void update() {
    raw = analogRead(SENSOR_PIN);

    if (raw != last_raw) {
      temp = m * raw + b;
      last_raw = raw;
    }
  }
}
