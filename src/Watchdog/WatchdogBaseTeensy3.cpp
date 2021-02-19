// ----------------------------------------------------------------------------
// WatchdogBaseTeensy3.cpp
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------

#include "WatchdogBaseTeensy3.h"

#if defined(__MK20DX128__) || defined(__MK20DX256__) || defined(__MK64FX512__) || defined(__MK66FX1M0__)


void WatchdogBase::reset()
{
  noInterrupts();

  WDOG_REFRESH = 0xA602;
  WDOG_REFRESH = 0xB480;

  interrupts();
}

bool WatchdogBase::tripped()
{
  return ( (RCM_SRS0 & RCM_SRS0_WDOG) != 0 );
}

void WatchdogBase::enable(int timeout_ms)
{
  const uint32_t WDT_CYCLES_PER_MS = F_CPU/10000;
  uint8_t REGISTER_BITS = 16;

  uint16_t tovalh = (uint16_t)((WDT_CYCLES_PER_MS*timeout_ms)>>REGISTER_BITS);
  uint16_t tovall = (uint16_t)(WDT_CYCLES_PER_MS*timeout_ms);

  noInterrupts();

  WDOG_UNLOCK = WDOG_UNLOCK_SEQ1;
  WDOG_UNLOCK = WDOG_UNLOCK_SEQ2;

  delayMicroseconds(1);

  WDOG_TOVALH = tovalh;
  WDOG_TOVALL = tovall;

  WDOG_PRESC  = 0x400;

  WDOG_STCTRLH |= WDOG_STCTRLH_ALLOWUPDATE |
    WDOG_STCTRLH_WDOGEN | WDOG_STCTRLH_WAITEN |
    WDOG_STCTRLH_STOPEN | WDOG_STCTRLH_CLKSRC;

  interrupts();
}

#endif
