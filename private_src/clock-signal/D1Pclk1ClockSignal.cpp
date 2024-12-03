#include "D1Pclk1ClockSignal.h"

bsp::D1Pclk1ClockSignal &bsp::D1Pclk1ClockSignal::Instance()
{
    class Getter :
        public base::SingletonGetter<D1Pclk1ClockSignal>
    {
    public:
        std::unique_ptr<D1Pclk1ClockSignal> Create() override
        {
            return std::unique_ptr<D1Pclk1ClockSignal>{new D1Pclk1ClockSignal{}};
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

std::string bsp::D1Pclk1ClockSignal::Name() const
{
    return "d1pclk1";
}

base::Hz bsp::D1Pclk1ClockSignal::Frequency() const
{
    uint32_t value = HAL_RCC_GetPCLK1Freq();
    return base::Hz{value};
}

void bsp::D1Pclk1ClockSignal::Open(bsp::IClockSignal_InputDivisionFactor const &input_division_factor)
{
    RCC_ClkInitTypeDef def{};
    def.ClockType = RCC_CLOCKTYPE_D1PCLK1;

    switch (input_division_factor.Value())
    {
    case 1:
        {
            def.APB3CLKDivider = RCC_APB3_DIV1;
            break;
        }
    case 2:
        {
            def.APB3CLKDivider = RCC_APB3_DIV2;
            break;
        }
    case 4:
        {
            def.APB3CLKDivider = RCC_APB3_DIV4;
            break;
        }
    case 8:
        {
            def.APB3CLKDivider = RCC_APB3_DIV8;
            break;
        }
    case 16:
        {
            def.APB3CLKDivider = RCC_APB3_DIV16;
            break;
        }
    default:
        {
            throw std::invalid_argument{"不支持此分频"};
        }
    }

    HAL_StatusTypeDef ret = HAL_RCC_ClockConfig(&def,
                                                FLASH_LATENCY_2);

    if (ret != HAL_StatusTypeDef::HAL_OK)
    {
        throw std::runtime_error{"时钟信号配置失败"};
    }
}
