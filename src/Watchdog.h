// ----------------------------------------------------------------------------
// Watchdog.h
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------

#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <Arduino.h>

#if defined(__AVR_ATmega32U4__) || defined(__AVR_AT90USB1286__)

#include "Watchdog/WatchdogBaseTeensy2.h"

#elif defined(__AVR__) && defined(MCUSR) && !defined(__AVR_ATmega32U4__) && !defined(__AVR_AT90USB1286__)

#include "Watchdog/WatchdogBaseAvr.h"

#elif defined(__AVR__) && defined(RSTCTRL_RSTFR)

#include "Watchdog/WatchdogBaseMegaavr.h"

#elif defined(__MK20DX128__) || defined(__MK20DX256__) || defined(__MK64FX512__) || defined(__MK66FX1M0__)

#include "Watchdog/WatchdogBaseTeensy3.h"

#elif defined(__IMXRT1062__)

#include "Watchdog/WatchdogBaseTeensy4.h"

#endif


class Watchdog : public WatchdogBase
{
public:
  enum Timeout {
    TIMEOUT_15MS=15,
    TIMEOUT_30MS=30,
    TIMEOUT_60MS=60,
    TIMEOUT_120MS=120, 
    TIMEOUT_250MS=250,
    TIMEOUT_500MS=500,
    TIMEOUT_1S=1000,
    TIMEOUT_2S=2000,
    TIMEOUT_4S=4000,
    TIMEOUT_8S=8000
  };
  Watchdog();
  void enable(Timeout timeout=TIMEOUT_1S);
  bool enabled();
  void reset();
  bool tripped();
private:
  bool enabled_;
};

#endif
