#include "PllClock.h"

std::string bsp::PllClock::Name() const
{
    return "pll";
}

void bsp::PllClock::Open(std::string const &input_channel_name)
{
    // 这里没有指定想要的输出频率，那就输出最大频率
}

void bsp::PllClock::Open(std::string const &input_channel_name,
                         base::IDictionary<std::string, base::Hz> const &target_output_frequencies)
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
