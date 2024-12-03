#include "Pclk1ClockSignal.h"

bsp::Pclk1ClockSignal &bsp::Pclk1ClockSignal::Instance()
{
    class Getter :
        public base::SingletonGetter<Pclk1ClockSignal>
    {
    public:
        std::unique_ptr<Pclk1ClockSignal> Create() override
        {
            return std::unique_ptr<Pclk1ClockSignal>{new Pclk1ClockSignal{}};
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

std::string bsp::Pclk1ClockSignal::Name() const
{
    return "pclk1";
}

base::Hz bsp::Pclk1ClockSignal::Frequency() const
{
    uint32_t value = HAL_RCC_GetPCLK1Freq();
    return base::Hz{value};
}
