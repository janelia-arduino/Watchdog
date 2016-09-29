#Watchdog

Authors:

    Peter Polidoro <polidorop@janelia.hhmi.org>

License:

    BSD

Use Watchdog to execute a function and/or reset the microcontroller
after a set amount of time passes, unless the timer is reset.

[Usage Examples](./examples)

##Execute Interrupt Service Routine (ISR) Function on Timeout

```cpp
void userFunc()
{
  //your code here
}
void setup()
{
  watchdog.enableIsr(userFunc);
}
```

##Reset Microcontroller on Timeout

```cpp
void setup()
{
  watchdog.enableSystemReset();
}
```

##Specify Timeout

```cpp
void setup()
{
  watchdog.begin(Watchdog::TIMEOUT_1000MS);
}
```

##Timeout Values

* Watchdog::TIMEOUT_16MS
* Watchdog::TIMEOUT_32MS
* Watchdog::TIMEOUT_64MS
* Watchdog::TIMEOUT_125MS
* Watchdog::TIMEOUT_250MS
* Watchdog::TIMEOUT_500MS
* Watchdog::TIMEOUT_1000MS
* Watchdog::TIMEOUT_2000MS
* Watchdog::TIMEOUT_4000MS
* Watchdog::TIMEOUT_8000MS

##Prevent Timeout

```cpp
// Call resetTimer before timeout duration expires. Repeat.
watchdog.resetTimer();
```

##Install Library Dependencies

[arduino-libraries](https://github.com/janelia-arduino/arduino-libraries)
