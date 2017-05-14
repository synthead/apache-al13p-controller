#include "relays.h"
#include <Arduino.h>

#define HEAT_PIN 14
#define REVERSE_PIN 15

namespace Relays {
  void setup() {
    pinMode(HEAT_PIN, OUTPUT);
    pinMode(REVERSE_PIN, OUTPUT);
  }

  void heat(bool on) {
    digitalWrite(HEAT_PIN, on);
  }

  void reverse(bool on) {
    digitalWrite(REVERSE_PIN, on);
  }
}
