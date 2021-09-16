// ----------------------------------------------------------------------------
// Watchdog.cpp
//
// Authors:
// Peter Polidoro peter@polidoro.io
// ----------------------------------------------------------------------------

#include "../Watchdog.h"


Watchdog::Watchdog()
  : enabled_{false}
{
}

void Watchdog::enable(Timeout timeout)
{
  WatchdogBase::enable(timeout);
  enabled_ = true;
}

bool Watchdog::enabled()
{
  return enabled_;
}

void Watchdog::reset()
{
  WatchdogBase::reset();
}

bool Watchdog::tripped()
{
  return WatchdogBase::tripped();
}
