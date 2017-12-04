// ----------------------------------------------------------------------------
// WatchdogTester.ino
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------

// This sample program shows how to use the watch dog timer (WDT).

// When program starts, it turns LED off for 1 seconds.
// It then turns LED on, and pauses for 5 seconds letting you know it is ready to start.
// WDT is initialized, and loop starts. It will flash led and reset wdt for the first 10 secs.
// After that, it stops resetting wdt. This causes the WDT to reboot and the cycle starts over.

#include <Arduino.h>
#include <Watchdog.h>


const long BAUDRATE = 115200;
const long SETUP_LED_OFF_DURATION = 1000;
const long SETUP_LED_ON_DURATION = 5000;
const long TIMEOUT_DURATION = 10000;
const long BLINK_HALF_PERIOD = 100;
const long RESET_DURATION = 500;

Watchdog watchdog;
unsigned long time_since_enabled;
unsigned long time_since_blink;
unsigned long time_since_reset;

void setup()
{
  // Setup serial communications
  Serial.begin(BAUDRATE);

  pinMode(LED_BUILTIN,OUTPUT);

  // Indicate we are starting over by hold led off
  digitalWrite(LED_BUILTIN,LOW);
  delay(SETUP_LED_OFF_DURATION);

  // Indicate we are in setup by hold LED on
  digitalWrite(LED_BUILTIN,HIGH);
  delay(SETUP_LED_ON_DURATION);

  // Setup WDT
  watchdog.enable(Watchdog::TIMEOUT_1S);

  time_since_enabled = millis();
  time_since_blink = time_since_enabled;
  time_since_reset = time_since_enabled;

}

void loop()
{
  const long time = millis();

  // Toggle led
  if ((time - time_since_blink) >= BLINK_HALF_PERIOD)
  {
    time_since_blink = time;
    digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));
  }

  // Stop resetting watchdog after timeout
  if (((time - time_since_enabled) <= TIMEOUT_DURATION) &&
      ((time - time_since_reset) >= RESET_DURATION))
  {
    time_since_reset = time;
    watchdog.reset();
  }
}
