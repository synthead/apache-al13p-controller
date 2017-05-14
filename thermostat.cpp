#include "thermostat.h"
#include "sensor.h"
#include "relays.h"

namespace Thermostat {
  // TODO: Allow user to set this value.
  // TODO: Read/write this value to/from EEPROM.
  // TODO: Add PID support.
  float desired_temp = 150.0;

  void update(float temp) {
    if (temp >= 150) {
      Relays::heat(false);
    } else {
      Relays::heat(true);
    }
  }
}
