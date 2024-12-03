#pragma once
#include <bsp-interface/clock/IClockSignal.h>

namespace bsp
{
    class SysclkClockSignal
    {
    public:
        /// @brief 打开时钟信号。
        /// @param output_division_factor 输出分频系数。
        /// @param clock_source 时钟源。像 stm32 的系统时钟 sysclk，是时钟源后的第一个时钟信号，输入端连接着
        /// 各个时钟源，输出端供给各个子时钟信号。本参数用来选择类似 sysclk 这种时钟信号的时钟源。
        virtual void Open(bsp::IClockSignal_OutputDivisionFactor const &output_division_factor,
                          IClockSignal_ClockSource const &clock_source);
    };
} // namespace bsp
