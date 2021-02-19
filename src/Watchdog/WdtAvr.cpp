// ----------------------------------------------------------------------------
// WdtAvr.cpp
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------

#include "WdtAvr.h"

#if defined(__AVR__)


void WdtAvr::reset()
{
  wdt_reset();
}

void WdtAvr::enable(int timeout_ms)
{
  uint8_t wdt_timeout = 0;

  switch (timeout_ms)
    {
    case 15:
      {
        wdt_timeout = WDTO_15MS;
        break;
      }
    case 30:
      {
        wdt_timeout = WDTO_30MS;
        break;
      }
    case 60:
      {
        wdt_timeout = WDTO_60MS;
        break;
      }
    case 120:
      {
        wdt_timeout = WDTO_120MS;
        break;
      }
    case 250:
      {
        wdt_timeout = WDTO_250MS;
        break;
      }
    case 500:
      {
        wdt_timeout = WDTO_500MS;
        break;
      }
    case 1000:
      {
        wdt_timeout = WDTO_1S;
        break;
      }
    case 2000:
      {
        wdt_timeout = WDTO_2S;
        break;
      }
    case 4000:
      {
        wdt_timeout = WDTO_4S;
        break;
      }
    case 8000:
      {
        wdt_timeout = WDTO_8S;
        break;
      }
    }

  wdt_enable(wdt_timeout);
}

#endif
