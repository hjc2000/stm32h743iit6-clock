#include <base/container/Dictionary.h>
#include <bsp-interface/di/clock.h>
#include <HseClock.h>

namespace
{
    class Initializer
    {
    public:
        Initializer()
        {
            _dic.Add("hse", &bsp::HseClock::Instance());
        }

        base::Dictionary<std::string, bsp::IClockSource *> _dic{};
    };
} // namespace

base::IDictionary<std::string, bsp::IClockSource *> const &DI_ClockSourceCollection()
{
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

    Getter g;
    return g.Instance()._dic;
}
