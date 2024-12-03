#include "Pclk2ClockSignal.h"

bsp::Pclk2ClockSignal &bsp::Pclk2ClockSignal::Instance()
{
    class Getter :
        public base::SingletonGetter<Pclk2ClockSignal>
    {
    public:
        std::unique_ptr<Pclk2ClockSignal> Create() override
        {
            return std::unique_ptr<Pclk2ClockSignal>{new Pclk2ClockSignal{}};
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

std::string bsp::Pclk2ClockSignal::Name() const
{
    return "pclk2";
}

base::Hz bsp::Pclk2ClockSignal::Frequency() const
{
    uint32_t value = HAL_RCC_GetPCLK2Freq();
    return base::Hz{value};
}
