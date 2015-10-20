#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "SPI.h"
#include "Streaming.h"
#include "Watchdog.h"

const int BAUDRATE = 9600;
const int LOOP_DELAY_MORE = 300;
const int LOOP_DELAY_LESS = 200;

void watchdogIsr()
{
  Serial << "Test isr!" << endl;
}

void setup()
{
  // Setup serial communications
  Serial.begin(BAUDRATE);

  // watchdog.enableSystemReset();
  watchdog.enableIsr(watchdogIsr);
  watchdog.begin(Watchdog::TIMEOUT_250MS);

  Serial << "System reset!" << endl;

}

void loop()
{
  watchdog.resetTimer();
  delay(LOOP_DELAY_MORE);
  // delay(LOOP_DELAY_LESS);
}
