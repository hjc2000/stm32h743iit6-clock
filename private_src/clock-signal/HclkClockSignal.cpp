#include "HclkClockSignal.h"

bsp::HclkClockSignal &bsp::HclkClockSignal::Instance()
{
    class Getter :
        public base::SingletonGetter<HclkClockSignal>
    {
    public:
        std::unique_ptr<HclkClockSignal> Create() override
        {
            return std::unique_ptr<HclkClockSignal>{new HclkClockSignal{}};
        }

        void Lock() override
        {
            DI_InterruptSwitch().DisableGlobalInterrupt();
        }

        void Unlock() override
        {
            DI_InterruptSwitch().EnableGlobalInterrupt();
        }
    };

    Getter g;
    return g.Instance();
}

std::string bsp::HclkClockSignal::Name() const
{
    return "hclk";
}

base::Hz bsp::HclkClockSignal::Frequency() const
{
    uint32_t value = HAL_RCC_GetHCLKFreq();
    return base::Hz{value};
}
