// ----------------------------------------------------------------------------
// Watchdog.h
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef WATCHDOG_H
#define WATCHDOG_H
#include <Arduino.h>
#if defined(__AVR__)
#include <avr/wdt.h>
#endif

class Watchdog
{
public:
  enum timeouts {TIMEOUT_15MS,
                 TIMEOUT_30MS,
                 TIMEOUT_60MS,
                 TIMEOUT_120MS,
                 TIMEOUT_250MS,
                 TIMEOUT_500MS,
                 TIMEOUT_1S,
                 TIMEOUT_2S,
                 TIMEOUT_4S,
                 TIMEOUT_8S,
  };
  Watchdog();
  void enable(timeouts timeout=TIMEOUT_1S);
  bool enabled();
  void reset();
private:
  bool enabled_;
};

#endif
