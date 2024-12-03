#pragma once
#include <base/define.h>
#include <base/di/SingletonGetter.h>
#include <bsp-interface/clock/IClockSignal.h>
#include <bsp-interface/di/interrupt.h>
#include <hal.h>

namespace bsp
{
    class Pclk1ClockSignal :
        public bsp::IClockSignal
    {
    public:
        static_function Pclk1ClockSignal &Instance();

        /// @brief 时钟信号的名称。
        /// @return
        virtual std::string Name() const override;

        /// @brief 时钟信号的频率
        /// @return
        virtual base::Hz Frequency() const override;
    };
} // namespace bsp
