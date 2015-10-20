// ----------------------------------------------------------------------------
// Watchdog.cpp
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------

#include "Watchdog.h"

Watchdog::Watchdog()
{
  system_reset_ = false;
  isr_enabled_ = false;
}

byte wdtcsr_display = 0;

void Watchdog::enableSystemReset()
{
  system_reset_ = true;
}

void Watchdog::enableIsr(void (*isr_func)())
{
  isr_func_ = isr_func;
  isr_enabled_ = true;
}

void Watchdog::begin(timeouts timeout)
{
  byte wdtcsr_byte = 0;
  switch (timeout)
  {
    case TIMEOUT_16MS:
      wdtcsr_byte = (0<<WDP3) | (0<<WDP2) | (0<<WDP1) | (0<<WDP0);
      break;
    case TIMEOUT_32MS:
      wdtcsr_byte = (0<<WDP3) | (0<<WDP2) | (0<<WDP1) | (1<<WDP0);
      break;
    case TIMEOUT_64MS:
      wdtcsr_byte = (0<<WDP3) | (0<<WDP2) | (1<<WDP1) | (0<<WDP0);
      break;
    case TIMEOUT_125MS:
      wdtcsr_byte = (0<<WDP3) | (0<<WDP2) | (1<<WDP1) | (1<<WDP0);
      break;
    case TIMEOUT_250MS:
      wdtcsr_byte = (0<<WDP3) | (1<<WDP2) | (0<<WDP1) | (0<<WDP0);
      break;
    case TIMEOUT_500MS:
      wdtcsr_byte = (0<<WDP3) | (1<<WDP2) | (0<<WDP1) | (1<<WDP0);
      break;
    case TIMEOUT_1000MS:
      wdtcsr_byte = (0<<WDP3) | (1<<WDP2) | (1<<WDP1) | (0<<WDP0);
      break;
    case TIMEOUT_2000MS:
      wdtcsr_byte = (0<<WDP3) | (1<<WDP2) | (1<<WDP1) | (1<<WDP0);
      break;
    case TIMEOUT_4000MS:
      wdtcsr_byte = (1<<WDP3) | (0<<WDP2) | (0<<WDP1) | (0<<WDP0);
      break;
    case TIMEOUT_8000MS:
      wdtcsr_byte = (1<<WDP3) | (0<<WDP2) | (0<<WDP1) | (1<<WDP0);
      break;
  }

  // Set Watchdog settings
  if (system_reset_)
  {
    wdtcsr_byte |= (1<<WDE);
  }
  if (isr_enabled_)
  {
    wdtcsr_byte |= (1<<WDIE);
  }

  // disable interrupts
  noInterrupts();

  // reset watchdog timer
  wdt_reset();

  // Clear WDRF in MCUSR
  MCUSR &= ~(1<<WDRF);

  // Enter Watchdog Configuration mode:
  // Write logical one to WDCE and WDE
  // Keep old prescaler setting to prevent unintentional time-out
  WDTCSR |= (1<<WDCE) | (1<<WDE);

  WDTCSR = wdtcsr_byte;

  interrupts();
}

void Watchdog::resetTimer()
{
  wdt_reset();
}

Watchdog watchdog;

ISR(WDT_vect)
{
  watchdog.isr();
}
