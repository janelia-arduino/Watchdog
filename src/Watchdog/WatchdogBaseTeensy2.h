// ----------------------------------------------------------------------------
// WatchdogBaseTeensy2.h
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------

#ifndef WATCHDOG_BASE_TEENSY2_H
#define WATCHDOG_BASE_TEENSY2_H

#include <Arduino.h>

#if defined(__AVR_ATmega32U4__) || defined(__AVR_AT90USB1286__)

#include <avr/wdt.h>
#include <avr/interrupt.h>

class WatchdogBase
{
public:
  void reset();
  bool tripped();
protected:
  void enable(int timeout_ms);
};

#endif
#endif
