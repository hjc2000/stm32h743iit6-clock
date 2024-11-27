#include "PllClock.h"

std::string bsp::PllClock::Name() const
{
    return "pll";
}

bsp::IClockSource_State bsp::PllClock::State() const
{
    return _state;
}
