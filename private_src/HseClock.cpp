#include "HseClock.h"
#include <hal.h>

std::string bsp::HseClock::Name() const
{
    return "hse";
}

void bsp::HseClock::TurnOn(base::Hz const &crystal_frequency,
                           int32_t input_division,
                           int32_t output_division)
{
    _frequency = crystal_frequency;
    _state = IClockSource_State::On;

    RCC_OscInitTypeDef def{};
    def.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    def.HSEState = RCC_HSE_ON;
    HAL_StatusTypeDef result = HAL_RCC_OscConfig(&def);
    if (result != HAL_StatusTypeDef::HAL_OK)
    {
        throw std::runtime_error{"打开 hse 时钟源失败。"};
    }
}

void bsp::HseClock::TurnOn(int32_t input_division, int32_t output_division)
{
    throw std::runtime_error{"hse 使用外部晶振，必须设置晶振频率，必须调用正确的 TurnOn 重载。"};
}

void bsp::HseClock::TurnOff()
{
    _state = IClockSource_State::Off;

    RCC_OscInitTypeDef def{};
    def.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    def.HSEState = RCC_HSE_OFF;

    HAL_StatusTypeDef result = HAL_RCC_OscConfig(&def);
    if (result != HAL_StatusTypeDef::HAL_OK)
    {
        throw std::runtime_error{"关闭 hse 时钟源失败。"};
    }
}

void bsp::HseClock::SetAsBypass(base::Hz external_clock_frequency,
                                int32_t input_division,
                                int32_t output_division)
{
    _frequency = external_clock_frequency;
    _state = IClockSource_State::Bypass;

    RCC_OscInitTypeDef def{};
    def.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    def.HSEState = RCC_HSE_BYPASS;

    HAL_StatusTypeDef result = HAL_RCC_OscConfig(&def);
    if (result != HAL_StatusTypeDef::HAL_OK)
    {
        throw std::runtime_error{"设置 hse 时钟源为旁路失败。"};
    }
}

bsp::IClockSource_State bsp::HseClock::State() const
{
    return _state;
}

base::Hz bsp::HseClock::Frequency() const
{
    return _frequency;
}
