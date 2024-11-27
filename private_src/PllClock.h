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
    public:
        /// @brief 本时钟源的名称。
        /// @return
        std::string Name() const override;

#pragma region Open
        /// @brief 打开时钟源。
        /// @param target_output_frequency 目标输出频率。
        virtual void Open(IClockSource_TargetOutputFrequency const &target_output_frequency);

        /// @brief 打开时钟源。
        /// @param target_output_frequencies 想让本时钟源输出的目标频率列表。因为有的时钟源可能有多个输出
        /// 通道，所以就采用了字典的形式。输出通道名为 key，目标频率为 value.
        virtual void Open(base::IDictionary<std::string, base::Hz> const &target_output_frequencies);
#pragma endregion

        /// @brief 关闭时钟源。
        virtual void Close() = 0;

        /// @brief 本时钟源当前的状态。
        /// @return
        virtual IClockSource_State State() const = 0;

        /// @brief 本时钟源当前频率。
        /// @return
        virtual base::Hz Frequency() const = 0;
    };
} // namespace bsp
