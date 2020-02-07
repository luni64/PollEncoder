#include "PollEncoder.h"

namespace PollEncoder
{
    void Encoder::tick()
    {
        int current = 0, diff;

        if (digitalReadFast(pinA)) current = 3;
        if (digitalReadFast(pinB)) current ^= 1;

        diff = last - current;
        if (diff & 1)
        {
            last = current;
            value.fetch_add((diff & 2) - 1);  // -> atomic version of value += (diff & 2) - 1)
        }
    }
}
