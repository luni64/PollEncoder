#pragma once

// https://www.mikrocontroller.net/articles/Drehgeber

#include "core_pins.h"
#include <atomic>

namespace PollEncoder
{
    class Encoder
    {
    public:
        Encoder(int _pinA, int _pinB, int mode = INPUT) : value(0), pinA(_pinA), pinB(_pinB)
        {
            pinMode(_pinA, mode);
            pinMode(_pinB, mode);
        }

        volatile std::atomic<int> value;   // use atomic since tick might be called by a timer ISR -> prevent issues

        void tick();

    protected:
        const int pinA, pinB;
        unsigned last;
    };
}
