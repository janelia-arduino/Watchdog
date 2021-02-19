// ----------------------------------------------------------------------------
// WatchdogBaseTeensy4.cpp
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------

#include "WatchdogBaseTeensy4.h"

#if defined(__IMXRT1062__)


void WatchdogBase::reset()
{
  wdt_.feed();
}

bool WatchdogBase::tripped()
{
  return ( (SRC_SRSR & 0x10) != 0);
}

void WatchdogBase::enable(int timeout_ms)
{
  uint32_t timeout_s = timeout_ms / 1000;
  if (timeout_s < 1)
    {
      timeout_s = 1;
    }
  WDT_timings_t config;
  config.timeout = timeout_s;
  wdt_.begin(config);
}

#endif
