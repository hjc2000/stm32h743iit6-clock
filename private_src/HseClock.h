#pragma once
#include <bsp-interface/clock/IClockSource.h>

namespace bsp
{
    class HseClock :
        public bsp::IClockSource
    {
    private:
        base::Hz _frequency{};
        IClockSource_State _state{};

    public:
#pragma region IClockSource
        /// @brief 本时钟源的名称。
        /// @return
        std::string Name() const override;

        /// @brief 打开时钟源。
        /// @param crystal_frequency 有的时钟源需要外部晶振，且晶振允许的频率是一个范围，
        /// 此时需要告诉本对象该晶振的频率才能打开本时钟源。这种情况下必须使用本 TurnOn 重载，
        /// 否则会抛出异常。
        /// @param input_division 输入分频系数。
        /// @param output_division 输出分频系数。
        void TurnOn(base::Hz const &crystal_frequency,
                    int32_t input_division,
                    int32_t output_division) override;

        /// @brief 打开时钟源。
        /// @param input_division 输入分频系数。
        /// @param output_division 输出分频系数。
        void TurnOn(int32_t input_division,
                    int32_t output_division) override;

        /// @brief 关闭时钟源。
        void TurnOff() override;

        /// @brief 设置为旁路。
        /// @param external_clock_frequency 外部时钟频率。
        /// @param input_division 输入分频系数。
        /// @param output_division 输出分频系数。
        void SetAsBypass(base::Hz external_clock_frequency,
                         int32_t input_division,
                         int32_t output_division) override;

        /// @brief 本时钟源当前的状态。
        /// @return
        IClockSource_State State() const override;

        /// @brief 本时钟源当前频率。
        /// @return
        base::Hz Frequency() const override;
#pragma endregion
    };
} // namespace bsp
