#include "thermostat.h"
#include "sensor.h"
#include "relays.h"
#include "settings.h"

namespace Thermostat {
  // TODO: Allow user to set this value.
  // TODO: Add PID support.
  void update(float temp) {
    if (temp >= Settings::settings.desired_temp) {
      Relays::heat(false);
    } else {
      Relays::heat(true);
    }
  }
}
