#include <base/container/Dictionary.h>
#include <bsp-interface/di/clock.h>
#include <HclkClockSignal.h>

namespace
{
    class Initializer
    {
    public:
        Initializer()
        {
            _dic.Add(bsp::HclkClockSignal::Instance().Name(), &bsp::HclkClockSignal::Instance());
        }

        base::Dictionary<std::string, bsp::IClockSignal *> _dic{};
    };

    /// @brief 单例获取器
    class Getter :
        public base::SingletonGetter<Initializer>
    {
    public:
        std::unique_ptr<Initializer> Create() override
        {
            return std::unique_ptr<Initializer>{new Initializer{}};
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
} // namespace

base::IDictionary<std::string, bsp::IClockSignal *> const &DI_ClockSignalCollection()
{
    Getter g;
    return g.Instance()._dic;
}
