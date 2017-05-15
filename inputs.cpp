#include "inputs.h"
#include "settings.h"
#include "menu.h"
#include "thermostat.h"
#include <Arduino.h>

#define INPUTS_ENCODER_A 8
#define INPUTS_ENCODER_B 9
#define INPUTS_AUTOTUNE 10

#define INPUTS_SETTINGS_WRITE_TIMEOUT 3000

namespace Inputs {
  bool encoder_a;
  bool encoder_b;
  bool autotune;

  bool last_encoder_a;
  bool last_encoder_b;
  bool last_autotune;

  bool pending_write = false;
  unsigned long write_millis;

  void setup() {
    pinMode(INPUTS_ENCODER_A, INPUT);
    pinMode(INPUTS_ENCODER_B, INPUT);
    pinMode(INPUTS_AUTOTUNE, INPUT);
  }

  void loop() {
    if (pending_write && millis() >= write_millis) {
      Settings::write_settings();
      pending_write = false;
    }

    encoder_a = digitalRead(INPUTS_ENCODER_A);
    encoder_b = digitalRead(INPUTS_ENCODER_B);
    autotune = digitalRead(INPUTS_AUTOTUNE);

    if (encoder_a && ! last_encoder_b && encoder_b) {
      Settings::settings.desired_temp++;
      Menu::temps();
      queue_write();
    }

    if (encoder_b && ! last_encoder_a && encoder_a) {
      Settings::settings.desired_temp--;
      Menu::temps();
      queue_write();
    }

    if (! last_autotune && autotune) {
      if (Thermostat::autotune_running) {
        Thermostat::cancel_autotune();
      } else {
        Thermostat::start_autotune();
      }
    }

    last_encoder_a = encoder_a;
    last_encoder_b = encoder_b;
    last_autotune = autotune;
  }

  void queue_write() {
    write_millis = millis() + INPUTS_SETTINGS_WRITE_TIMEOUT;
    pending_write = true;
  }
}
