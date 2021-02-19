// ----------------------------------------------------------------------------
// WdtAvr.h
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------

#ifndef WDT_AVR_H
#define WDT_AVR_H

#if defined(__AVR__)

#include <avr/wdt.h>

#if !defined(WDTO_4S)

#define WDTO_4S WDTO_1S

#endif

#if !defined(WDTO_8S)

#define WDTO_8S WDTO_1S

#endif


class WdtAvr
{
public:
  void reset();
protected:
  void enable(int timeout_ms);
};

#endif
#endif
