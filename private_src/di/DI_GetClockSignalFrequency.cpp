#include <bsp-interface/di/clock.h>
#include <hal.h>

base::Hz DI_GetClockSignalFrequency(std::string const &clock_signal_name)
{
    if (clock_signal_name == "hclk")
    {
        uint32_t value = HAL_RCC_GetHCLKFreq();
        return base::Hz{value};
    }

    return base::Hz{0};
}
