// ----------------------------------------------------------------------------
// WatchdogBaseMegaavr.cpp
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------

#include "WatchdogBaseMegaavr.h"

#if defined(__AVR__) && defined(RSTCTRL_RSTFR)


bool WatchdogBase::tripped()
{
  return ( (RSTCTRL_RSTFR & (1<<RSTCTRL_WDRF_bp)) != 0 );
}

#endif
