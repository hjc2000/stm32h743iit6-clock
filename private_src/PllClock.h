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
        /// @brief 用户自己决定输入通道和各个分频、倍频系数。
        /// @param input_channel_name 输入通道名。
        /// @param factor 分频、倍频系数都放在这个字典里，使用不同的名称来区分是什么。
        void Open(std::string const &input_channel_name, base::IDictionary<std::string, int> const &factor) override;
#pragma endregion

        /// @brief 关闭时钟源。
        void Close() override;

        /// @brief 本时钟源当前的状态。
        /// @return
        IClockSource_State State() const override;

        /// @brief 本时钟源当前频率。
        /// @return
        base::Hz Frequency() const override;
    };
} // namespace bsp
