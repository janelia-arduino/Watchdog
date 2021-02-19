// ----------------------------------------------------------------------------
// WatchdogBaseTeensy4.h
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------

#ifndef WATCHDOG_BASE_TEENSY4_H
#define WATCHDOG_BASE_TEENSY4_H

#if defined(__IMXRT1062__)

#include "WdtTeensy4.h"


class WatchdogBase
{
public:
  void reset();
  bool tripped();
protected:
  void enable(int timeout_ms);
private:
  WDT_T4<WDT1> wdt_;
};

#endif
#endif
