#include "PllClock.h"

std::string bsp::PllClock::Name() const
{
    return "pll";
}

void bsp::PllClock::Open(std::string const &input_channel_name, base::IDictionary<std::string, int> const &factor)
{
}

void bsp::PllClock::Close()
{
}

bsp::IClockSource_State bsp::PllClock::State() const
{
    return _state;
}

base::Hz bsp::PllClock::Frequency() const
{
    return base::Hz();
}
