// ----------------------------------------------------------------------------
// WatchdogTester.ino
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------

// This sample program shows how to use the watchdog timer.

// When the device first powers on, it turns the LED off for 1 seconds. It then
// turns the LED on, and pauses for 4 seconds letting you know it is ready to
// start. Watchdog is initialized and the loop starts. It will flash the LED and
// reset watchdog for the first 6 secs. After that, it stops resetting watchdog.
// This causes the watchdog to reboot the device. When the device powers on
// after a watchdog device reset, it blinks the LED twice for 1.5 seconds before
// flashing the LED to let you know the watchdog had been previously tripped.

#include <Watchdog.h>


const unsigned long SETUP_LED_OFF_DURATION = 1000;
const unsigned long SETUP_LED_ON_IF_NOT_TRIPPED_DURATION = 4000;
const unsigned long SETUP_LED_ON_IF_TRIPPED_DURATION = 1500;
const unsigned long TIMEOUT_DURATION = 6000;
const unsigned long BLINK_HALF_PERIOD = 100;
const unsigned long RESET_DURATION = 500;

Watchdog watchdog;
unsigned long enabled_time;
unsigned long blink_time;
unsigned long reset_time;

void setLedOff()
{
  digitalWrite(LED_BUILTIN,LOW);
  delay(SETUP_LED_OFF_DURATION);
}

void setLedOn(unsigned long duration)
{
  digitalWrite(LED_BUILTIN,HIGH);
	delay(duration);
}

void toggleLed()
{
	digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));
}

void setup()
{
  pinMode(LED_BUILTIN,OUTPUT);

  // Indicate we are starting over by holding led off
	setLedOff();

  // Indicate we are in setup by holding LED on
	if (!watchdog.tripped())
	{
		// blink once to indicate power cycle reset
		setLedOn(SETUP_LED_ON_IF_NOT_TRIPPED_DURATION);
	}
	else
	{
		// blink twice to indicate watchdog tripped reset
		setLedOn(SETUP_LED_ON_IF_TRIPPED_DURATION);
		setLedOff();
		setLedOn(SETUP_LED_ON_IF_TRIPPED_DURATION);
	}

  // Setup watchdog
  watchdog.enable(Watchdog::TIMEOUT_1S);

  enabled_time = millis();
  blink_time = enabled_time;
  reset_time = enabled_time;
}

void loop()
{
  const unsigned long time = millis();

  // Toggle led
  if ((time - blink_time) >= BLINK_HALF_PERIOD)
  {
    blink_time = time;
		toggleLed();
  }

  // Stop resetting watchdog after timeout
  if (((time - enabled_time) <= TIMEOUT_DURATION) &&
    ((time - reset_time) >= RESET_DURATION))
  {
    reset_time = time;
    watchdog.reset();
  }
}
