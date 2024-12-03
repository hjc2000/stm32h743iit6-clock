#include "SysclkClockSignal.h"

bsp::SysclkClockSignal &bsp::SysclkClockSignal::Instance()
{
    class Getter :
        public base::SingletonGetter<SysclkClockSignal>
    {
    public:
        std::unique_ptr<SysclkClockSignal> Create() override
        {
            return std::unique_ptr<SysclkClockSignal>{new SysclkClockSignal{}};
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

std::string bsp::SysclkClockSignal::Name() const
{
    return "sysclk";
}

base::Hz bsp::SysclkClockSignal::Frequency() const
{
    uint32_t value = HAL_RCC_GetSysClockFreq();
    return base::Hz{value};
}

void bsp::SysclkClockSignal::Open(bsp::IClockSignal_OutputDivisionFactor const &output_division_factor,
                                  IClockSignal_ClockSource const &clock_source)
{
}
