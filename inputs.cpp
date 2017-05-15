#include "inputs.h"
#include "settings.h"
#include "menu.h"
#include <Arduino.h>

#define INPUTS_ENCODER_A 8
#define INPUTS_ENCODER_B 9

namespace Inputs {
  bool encoder_a;
  bool encoder_b;

  bool last_encoder_a;
  bool last_encoder_b;

  void setup() {
    pinMode(INPUTS_ENCODER_A, INPUT);
    pinMode(INPUTS_ENCODER_B, INPUT);
  }

  void loop() {
    encoder_a = digitalRead(INPUTS_ENCODER_A);
    encoder_b = digitalRead(INPUTS_ENCODER_B);

    if (encoder_a && ! last_encoder_b && encoder_b) {
      Settings::settings.desired_temp++;
      Menu::update();
    }

    if (encoder_b && ! last_encoder_a && encoder_a) {
      Settings::settings.desired_temp--;
      Menu::update();
    }

    last_encoder_a = encoder_a;
    last_encoder_b = encoder_b;
  }
}
