#include "HseClock.h"

bsp::HseClock &bsp::HseClock::Instance()
{
    class Getter :
        public base::SingletonGetter<HseClock>
    {
    public:
        std::unique_ptr<HseClock> Create() override
        {
            return std::unique_ptr<HseClock>{new HseClock{}};
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

std::string bsp::HseClock::Name() const
{
    return "hse";
}

void bsp::HseClock::Open(base::Hz const &crystal_frequency)
{
    RCC_OscInitTypeDef def{};
    def.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    def.HSEState = RCC_HSE_ON;
    HAL_StatusTypeDef result = HAL_RCC_OscConfig(&def);
    if (result != HAL_StatusTypeDef::HAL_OK)
    {
        throw std::runtime_error{"打开 hse 时钟源失败。"};
    }

    _frequency = crystal_frequency;
    _state = IClockSource_State::On;
}

void bsp::HseClock::SetAsBypass(base::Hz external_clock_frequency)
{
    RCC_OscInitTypeDef def{};
    def.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    def.HSEState = RCC_HSE_BYPASS;

    HAL_StatusTypeDef result = HAL_RCC_OscConfig(&def);
    if (result != HAL_StatusTypeDef::HAL_OK)
    {
        throw std::runtime_error{"设置 hse 时钟源为旁路失败。"};
    }

    _frequency = external_clock_frequency;
    _state = IClockSource_State::Bypass;
}

void bsp::HseClock::Close()
{
    RCC_OscInitTypeDef def{};
    def.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    def.HSEState = RCC_HSE_OFF;

    HAL_StatusTypeDef result = HAL_RCC_OscConfig(&def);
    if (result != HAL_StatusTypeDef::HAL_OK)
    {
        throw std::runtime_error{"关闭 hse 时钟源失败。"};
    }

    _frequency = 0;
    _state = IClockSource_State::Off;
}

bsp::IClockSource_State bsp::HseClock::State() const
{
    return _state;
}

base::Hz bsp::HseClock::Frequency() const
{
    return _frequency;
}
