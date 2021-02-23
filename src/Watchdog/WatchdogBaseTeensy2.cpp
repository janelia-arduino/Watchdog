// ----------------------------------------------------------------------------
// WatchdogBaseTeensy2.cpp
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------

#include "WatchdogBaseTeensy2.h"

#if defined(__AVR_ATmega32U4__) || defined(__AVR_AT90USB1286__)


//WDT Interrupt which will soft reset the board
ISR(WDT_vect)
{
  wdt_disable();
  _restart_Teensyduino_();
}

void WatchdogBase::reset()
{
  wdt_reset();
}

bool WatchdogBase::tripped()
{
  return ( (MCUSR & (1<<WDRF)) != 0 );
}

void WatchdogBase::enable(int timeout_ms)
{
  uint8_t wdtcsr_byte = 0;

  switch (timeout_ms)
    {
    case 15:
      {
        wdtcsr_byte = WDTO_15MS;
        break;
      }
    case 30:
      {
        wdtcsr_byte = WDTO_30MS;
        break;
      }
    case 60:
      {
        wdtcsr_byte = WDTO_60MS;
        break;
      }
    case 120:
      {
        wdtcsr_byte = WDTO_120MS;
        break;
      }
    case 250:
      {
        wdtcsr_byte = WDTO_250MS;
        break;
      }
    case 500:
      {
        wdtcsr_byte = WDTO_500MS;
        break;
      }
    case 1000:
      {
        wdtcsr_byte = WDTO_1S;
        break;
      }
    case 2000:
      {
        wdtcsr_byte = WDTO_2S;
        break;
      }
    case 4000:
      {
        wdtcsr_byte = WDTO_4S;
        break;
      }
    case 8000:
      {
        wdtcsr_byte = WDTO_8S;
        break;
      }
    }

  // Clear WDRF in MCUSR
  MCUSR &= ~(1<<WDRF);

  noInterrupts();

  // The Watchdog Timer should be reset before any change of the WDP bits, since
  // a change in the WDP bits can result in a time-out when switching to a
  // shorter time-out period.
  wdt_reset();

  // Enter Watchdog Configuration mode
  WDTCSR |= (1<<WDCE) | (1<<WDE);

  // Enable watchdog interrupt mode
  wdtcsr_byte |= (1<<WDIE);

  // Set watchdog timer control register
  WDTCSR = wdtcsr_byte;
  
  interrupts();

}

#endif
