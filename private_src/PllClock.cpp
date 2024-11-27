#include "PllClock.h"

std::string bsp::PllClock::Name() const
{
    return "pll";
}

void bsp::PllClock::Open(std::string const &input_channel_name, base::IDictionary<std::string, int> const &factors)
{
    int m = 1;

    {
        int const *ptr = factors.Find("m");
        if (ptr != nullptr)
        {
            m = *ptr;
        }
    }

    int n = 1;

    {
        int const *ptr = factors.Find("n");
        if (ptr != nullptr)
        {
            n = *ptr;
        }
    }

    int p = 1;

    {
        int const *ptr = factors.Find("p");
        if (ptr != nullptr)
        {
            p = *ptr;
        }
    }

    int q = 1;

    {
        int const *ptr = factors.Find("q");
        if (ptr != nullptr)
        {
            q = *ptr;
        }
    }

    int r = 1;

    {
        int const *ptr = factors.Find("r");
        if (ptr != nullptr)
        {
            r = *ptr;
        }
    }
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
