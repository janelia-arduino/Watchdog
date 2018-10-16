// ----------------------------------------------------------------------------
// Watchdog.cpp
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#include "Watchdog.h"


Watchdog::Watchdog()
{
  enabled_ = false;
}

void Watchdog::enable(Timeout timeout)
{
#if defined(__AVR__)

  uint8_t wdtcsr_byte = 0;

  switch (timeout)
  {
    case TIMEOUT_15MS:
    {
      wdtcsr_byte = WDTO_15MS;
      break;
    }
    case TIMEOUT_30MS:
    {
      wdtcsr_byte = WDTO_30MS;
      break;
    }
    case TIMEOUT_60MS:
    {
      wdtcsr_byte = WDTO_60MS;
      break;
    }
    case TIMEOUT_120MS:
    {
      wdtcsr_byte = WDTO_120MS;
      break;
    }
    case TIMEOUT_250MS:
    {
      wdtcsr_byte = WDTO_250MS;
      break;
    }
    case TIMEOUT_500MS:
    {
      wdtcsr_byte = WDTO_250MS;
      break;
    }
    case TIMEOUT_1S:
    {
      wdtcsr_byte = WDTO_1S;
      break;
    }
    case TIMEOUT_2S:
    {
      wdtcsr_byte = WDTO_1S;
      break;
    }
    case TIMEOUT_4S:
    {
      wdtcsr_byte = WDTO_1S;
      break;
    }
    case TIMEOUT_8S:
    {
      wdtcsr_byte = WDTO_8S;
      break;
    }
  }

  // Set Watchdog settings

  // Enable system reset
  wdtcsr_byte |= (1<<WDE);

  noInterrupts();

  // Reset watchdog timer
  wdt_reset();

  // Clear WDRF in MCUSR
  MCUSR &= ~(1<<WDRF);

  // Enter Watchdog Configuration mode:
  // Write logical one to WDCE and WDE
  // Keep old prescaler setting to prevent unintentional time-out
  WDTCSR |= (1<<WDCE) | (1<<WDE);

  WDTCSR = wdtcsr_byte;

  interrupts();

  enabled_ = true;

#elif defined(__MK20DX128__) || defined(__MK20DX256__) || defined(__MK64FX512__) || defined(__MK66FX1M0__)

  const uint32_t WDT_CYCLES_PER_MS = F_CPU/10000;
  uint8_t REGISTER_BITS = 16;

  uint32_t timeout_ms = 1000;

  switch (timeout)
  {
    case TIMEOUT_15MS:
    {
      timeout_ms = 15;
      break;
    }
    case TIMEOUT_30MS:
    {
      timeout_ms = 30;
      break;
    }
    case TIMEOUT_60MS:
    {
      timeout_ms = 60;
      break;
    }
    case TIMEOUT_120MS:
    {
      timeout_ms = 120;
      break;
    }
    case TIMEOUT_250MS:
    {
      timeout_ms = 250;
      break;
    }
    case TIMEOUT_500MS:
    {
      timeout_ms = 500;
      break;
    }
    case TIMEOUT_1S:
    {
      timeout_ms = 1000;
      break;
    }
    case TIMEOUT_2S:
    {
      timeout_ms = 2000;
      break;
    }
    case TIMEOUT_4S:
    {
      timeout_ms = 4000;
      break;
    }
    case TIMEOUT_8S:
    {
      timeout_ms = 8000;
      break;
    }
  }

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

  enabled_ = true;

#else

#endif
}

bool Watchdog::enabled()
{
  return enabled_;
}

void Watchdog::reset()
{
#if defined(__AVR__)

  wdt_reset();

#elif defined(__MK20DX128__) || defined(__MK20DX256__) || defined(__MK64FX512__) || defined(__MK66FX1M0__)

  noInterrupts();

  WDOG_REFRESH = 0xA602;
  WDOG_REFRESH = 0xB480;

  interrupts();

#endif
}
