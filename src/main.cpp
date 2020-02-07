#include "Arduino.h"
#include "pollEncoder.h"

using namespace PollEncoder;

Encoder enc1(0, 1, INPUT_PULLUP);
Encoder enc2(2, 3, INPUT_PULLUP);

void setup()
{
  while(!Serial);

  Serial.println("Start");
}

int oldV1 = 0, oldV2 = 0;

void loop()
{
    enc1.tick();
    enc2.tick();

    int v1 = enc1.value;
    int v2 = enc2.value;

    if (v1 != oldV1 || v2 != oldV2)
    {
        oldV1 = v1;
        oldV2 = v2;
        Serial.printf("v1:%d v2:%d\n", v1, v2);
    }
}
