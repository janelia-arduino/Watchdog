// ----------------------------------------------------------------------------
// Watchdog.h
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef WATCHDOG_H
#define WATCHDOG_H
#include <Arduino.h>
#if defined(__AVR__)
#include <avr/wdt.h>
#endif
#if defined(__IMXRT1062__)
#include <Watchdog_t4.h>
#endif

class Watchdog
{
public:
  enum Timeout {TIMEOUT_15MS,
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
  void enable(Timeout timeout=TIMEOUT_1S);
  bool enabled();
  void reset();
private:
  bool enabled_;
#if defined(__IMXRT1062__)
  WDT_T4<WDT1> wdt_;
#endif
};

#endif
