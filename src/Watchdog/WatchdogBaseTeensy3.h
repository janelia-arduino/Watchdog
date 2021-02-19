// ----------------------------------------------------------------------------
// WatchdogBaseTeensy3.h
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------

#ifndef WATCHDOG_BASE_TEENSY3_H
#define WATCHDOG_BASE_TEENSY3_H

#include <Arduino.h>

#if defined(__MK20DX128__) || defined(__MK20DX256__) || defined(__MK64FX512__) || defined(__MK66FX1M0__)


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
