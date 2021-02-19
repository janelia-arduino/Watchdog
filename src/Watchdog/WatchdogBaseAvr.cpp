// ----------------------------------------------------------------------------
// WatchdogBaseAvr.cpp
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------

#include "WatchdogBaseAvr.h"

#if defined(__AVR__) && defined(MCUSR) && !defined(__AVR_ATmega32U4__) && !defined(__AVR_AT90USB1286__)


bool WatchdogBase::tripped()
{
  return ( (MCUSR & (1<<WDRF)) != 0 );
}

#endif
