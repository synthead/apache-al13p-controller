#include "thermostat.h"
#include "sensor.h"
#include "relays.h"
#include "settings.h"
#include <Arduino.h>
#include <PID_v1.h>
#include <PID_AutoTune_v0.h>

#define PID_OUTPUT_RANGE 100
#define PID_WINDOW_MS 1500
#define PID_LOOKBACK_S 30
#define PID_NOISE_BAND 0.1

#define PID_HEAT_THRESHOLD 70
#define PID_HEAT_DELTA 30

namespace Thermostat {
  bool heat_on = false;

  unsigned long window_end_millis;
  double pid_output;
  double pid_output_sum;
  int pid_output_count;
  double pid_output_average = 0.0;

  bool autotune_running = false;

  PID pid(
    &Sensor::temp,
    &pid_output,
    &Settings::settings.desired_temp,
    Settings::settings.pid_kp,
    Settings::settings.pid_ki,
    Settings::settings.pid_kd,
    DIRECT
  );

  PID_ATune pid_autotune(&Sensor::temp, &pid_output);

  void setup() {
    pid.SetOutputLimits(-PID_OUTPUT_RANGE, PID_OUTPUT_RANGE);

    pid_autotune.SetOutputStep(PID_OUTPUT_RANGE);
    pid_autotune.SetControlType(1);  // PID control type.

    pid.SetMode(AUTOMATIC);

    update_pid_tunings();
    reset_window();
  }

  void loop() {
    if (autotune_running) {
      if (pid_autotune.Runtime()) {
        autotune_running = false;

        Settings::settings.pid_kp = pid_autotune.GetKp();
        Settings::settings.pid_ki = pid_autotune.GetKi();
        Settings::settings.pid_kd = pid_autotune.GetKd();

        update_pid_tunings();
        Settings::write_settings();
      }
    }

    if (! autotune_running) {
      pid.Compute();
    }

    pid_output_sum += pid_output;
    pid_output_count++;

    unsigned long now = millis();
    if (now >= window_end_millis) {
      pid_output_average = pid_output_sum / pid_output_count;

      if (pid_output_average >= PID_HEAT_THRESHOLD) {
        set_heat(true);
      } else if (pid_output_average + PID_HEAT_DELTA <= PID_HEAT_THRESHOLD) {
        set_heat(false);
      }

      reset_window();
    }
  }

  void set_heat(bool new_heat_on) {
    heat_on = new_heat_on;
    Relays::heat(heat_on);
  }

  void update_pid_tunings() {
    pid.SetTunings(
      Settings::settings.pid_kp,
      Settings::settings.pid_ki,
      Settings::settings.pid_kd
    );
  }

  void reset_window() {
    window_end_millis = millis() + PID_WINDOW_MS;
    pid_output_sum = 0.0;
    pid_output_count = 0;
  }

  void start_autotune() {
    pid_autotune.SetLookbackSec(PID_LOOKBACK_S);
    pid_autotune.SetNoiseBand(PID_NOISE_BAND);

    autotune_running = true;
  }

  void cancel_autotune() {
    if (autotune_running) {
      pid_autotune.Cancel();
      autotune_running = false;
    }
  }
}
