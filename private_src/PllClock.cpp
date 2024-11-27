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

    RCC_OscInitTypeDef def{};
    def.OscillatorType = RCC_OSCILLATORTYPE_NONE;
    def.PLL.PLLState = RCC_PLL_ON;
    def.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    def.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
    def.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
    def.PLL.PLLM = m;
    def.PLL.PLLN = n;
    def.PLL.PLLP = p;
    def.PLL.PLLQ = q;
    def.PLL.PLLR = r;

    HAL_StatusTypeDef result = HAL_RCC_OscConfig(&def);
    if (result != HAL_StatusTypeDef::HAL_OK)
    {
        throw std::runtime_error{"时钟源配置失败"};
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
