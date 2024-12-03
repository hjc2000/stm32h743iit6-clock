#include "PclkClockSignal.h"

bsp::PclkClockSignal &bsp::PclkClockSignal::Instance()
{
    class Getter :
        public base::SingletonGetter<PclkClockSignal>
    {
    public:
        std::unique_ptr<PclkClockSignal> Create() override
        {
            return std::unique_ptr<PclkClockSignal>{new PclkClockSignal{}};
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

std::string bsp::PclkClockSignal::Name() const
{
    return "pclk1";
}

base::Hz bsp::PclkClockSignal::Frequency() const
{
    uint32_t value = HAL_RCC_GetPCLK1Freq();
    return base::Hz{value};
}
