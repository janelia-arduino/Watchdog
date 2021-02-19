// ----------------------------------------------------------------------------
// WatchdogBaseMegaavr.h
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------

#ifndef WATCHDOG_BASE_MEGAAVR_H
#define WATCHDOG_BASE_MEGAAVR_H

#include <Arduino.h>

#if defined(__AVR__) && defined(RSTCTRL_RSTFR)

#include "WdtAvr.h"


class WatchdogBase : public WdtAvr
{
public:
  bool tripped();
};

#endif
#endif
