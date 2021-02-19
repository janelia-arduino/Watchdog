// ----------------------------------------------------------------------------
// WatchdogBaseAvr.h
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------

#ifndef WATCHDOG_BASE_AVR_H
#define WATCHDOG_BASE_AVR_H

#include <Arduino.h>

#if defined(__AVR__) && defined(MCUSR) && !defined(__AVR_ATmega32U4__) && !defined(__AVR_AT90USB1286__)

#include "WdtAvr.h"


class WatchdogBase : public WdtAvr
{
public:
  bool tripped();
};

#endif
#endif
