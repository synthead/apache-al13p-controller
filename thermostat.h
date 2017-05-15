#ifndef THERMOSTAT_H
#define THERMOSTAT_H

namespace Thermostat {
  extern bool heat_on;
  extern bool autotune_running;

  void setup();
  void loop();
  void set_heat(bool);
  void update_pid_tunings();
  void reset_window();
  void start_autotune();
  void cancel_autotune();
}

#endif
