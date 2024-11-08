#pragma once
#include <bsp-interface/clock/IClockSource.h>

namespace bsp
{
    class HseClock :
        public bsp::IClockSource
    {
    public:
        /// @brief 本时钟源的名称。
        /// @return
        std::string Name() const override;

        /// @brief 打开时钟源。
        /// @param input_division 输入分频系数。
        /// @param output_division 输出分频系数。
        virtual void TurnOn(int32_t input_division,
                            int32_t output_division) = 0;

        /// @brief 关闭时钟源。
        virtual void TurnOff() = 0;

        /// @brief 设置为旁路。
        /// @param external_clock_frequency 外部时钟频率。
        /// @param input_division 输入分频系数。
        /// @param output_division 输出分频系数。
        virtual void SetAsBypass(base::Hz external_clock_frequency,
                                 int32_t input_division,
                                 int32_t output_division) = 0;

        /// @brief 本时钟源当前的状态。
        /// @return
        virtual IClockSource_State State() const = 0;

        /// @brief 本时钟源当前频率。
        /// @return
        virtual base::Hz Frequency() const = 0;
    };
} // namespace bsp
