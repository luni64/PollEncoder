# This library is obsolete please use https://github.com/luni64/EncPlex instead. 

---------------------------

# PollEncoder

PollEncoder is a small class to read encoders using the polling technique instead of the usual interrupt based method.

Advantage: If you have a lot high speed or bouncy encoders, the generated interrupts can lead to a high and unpredictable load.

Usage:

```c++
#include "Arduino.h"
#include "pollEncoder.h"

using namespace PollEncoder;

Encoder enc(0, 1, INPUT_PULLUP); // generate an encoder on pins 0/1

void setup()
{
  while(!Serial);
  Serial.println("Start");
}

int old_value;

void loop()
{
    enc.tick(); // call this as often as possible

    int value = enc.value;

    if (value != old_value)
    {
        old_value = value;
        Serial.printf("v:%d\n", value);
    }
}
```


Using an array of encoders:

```c++
#include "Arduino.h"
#include "pollEncoder.h"

using namespace PollEncoder;

Encoder enc[]{{0, 1}, {2, 3}, {4, 5}}; // encoders on 0/1, 2/3 and 4/5;

constexpr int nrOfEncoders = sizeof(enc) / sizeof(enc[0]);


void tickAll()
{
    for (int i = 0; i < nrOfEncoders; i++)
    {
        enc[i].tick();
    }
}

IntervalTimer timer;

void setup()
{
    while (!Serial);
    Serial.println("Start");

    // call the tick functions in the background from a timer;
    // tickfreqency 2kHz, should be more than enough for manual encoders
    timer.begin(tickAll, 500);
}

void loop()
{
    for (int i = 0; i < nrOfEncoders; i++)
    {
        Serial.printf("encoder%d: %d\n", i, enc[i].value);
    }
    Serial.println("----------------------------------");

    delay(200);
}
```
