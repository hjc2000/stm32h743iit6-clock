#pragma once
#include <base/define.h>
#include <base/di/SingletonGetter.h>
#include <bsp-interface/clock/IClockSource.h>
#include <bsp-interface/di/interrupt.h>
#include <hal.h>

namespace bsp
{
    class PllClock :
        public bsp::IClockSource
    {
    private:
        IClockSource_State _state = IClockSource_State::Off;

    public:
        /// @brief 本时钟源的名称。
        /// @return
        std::string Name() const override;

#pragma region Open
        /// @brief 打开时钟源。
        /// @param input_channel_name 输入通道名称。有的时钟源可能具有多个输入通道，例如可以从多个晶振中选择一个，
        /// 或者 PLL 可以从多个时钟源中选择一个。
        virtual void Open(std::string const &input_channel_name);

        /// @brief 打开时钟源。
        /// @param input_channel_name 输入通道名称。有的时钟源可能具有多个输入通道，例如可以从多个晶振中选择一个，
        /// 或者 PLL 可以从多个时钟源中选择一个。
        /// @param target_output_frequencies 想让本时钟源输出的目标频率列表。因为有的时钟源可能有多个输出
        /// 通道，所以就采用了字典的形式。输出通道名为 key，目标频率为 value.
        virtual void Open(std::string const &input_channel_name,
                          base::IDictionary<std::string, base::Hz> const &target_output_frequencies);
#pragma endregion

        /// @brief 关闭时钟源。
        virtual void Close() = 0;

        /// @brief 本时钟源当前的状态。
        /// @return
        IClockSource_State State() const override;

        /// @brief 本时钟源当前频率。
        /// @return
        virtual base::Hz Frequency() const = 0;
    };
} // namespace bsp
