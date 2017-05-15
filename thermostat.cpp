#include "thermostat.h"
#include "sensor.h"
#include "relays.h"
#include "settings.h"

namespace Thermostat {
  bool heat_on = false;

  // TODO: Add PID support.
  void update(float temp) {
    heat_on = temp < Settings::settings.desired_temp;
    Relays::heat(heat_on);
  }
}
