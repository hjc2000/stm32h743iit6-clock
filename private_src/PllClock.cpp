#include "PllClock.h"

std::string bsp::PllClock::Name() const
{
    return "pll";
}

void bsp::PllClock::Open(std::string const &input_channel_name, base::IDictionary<std::string, int> const &factors)
{
}

void bsp::PllClock::Close()
{
}

bsp::IClockSource_State bsp::PllClock::State() const
{
    return _state;
}

base::Hz bsp::PllClock::Frequency(std::string const &output_channel_name) const
{
    return base::Hz();
}
