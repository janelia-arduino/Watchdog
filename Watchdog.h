// ----------------------------------------------------------------------------
// Watchdog.h
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------

#ifndef WATCHDOG_H
#define WATCHDOG_H
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <avr/wdt.h>
#include "Streaming.h"


class Watchdog
{
public:
  enum timeouts {TIMEOUT_16MS,
                 TIMEOUT_32MS,
                 TIMEOUT_64MS,
                 TIMEOUT_125MS,
                 TIMEOUT_250MS,
                 TIMEOUT_500MS,
                 TIMEOUT_1000MS,
                 TIMEOUT_2000MS,
                 TIMEOUT_4000MS,
                 TIMEOUT_8000MS,
  };
  Watchdog();
  void enableSystemReset();
  void enableIsr(void (*isr_func)());
  void init(boolean system_reset=false);
  void begin(timeouts timeout=TIMEOUT_1000MS);
  void resetTimer();
  void isr();
private:
  boolean system_reset_;
  boolean isr_enabled_;
  void (*isr_func_)();
};

extern Watchdog watchdog;

inline void Watchdog::isr()
{
  (*isr_func_)();
}

#endif

