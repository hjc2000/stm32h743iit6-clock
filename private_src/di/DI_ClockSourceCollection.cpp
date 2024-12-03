#include <base/container/Dictionary.h>
#include <bsp-interface/di/clock.h>
#include <HseClockSource.h>
#include <PllClockSource.h>

namespace
{
    class Initializer
    {
    public:
        Initializer()
        {
            _dic.Add(bsp::HseClockSource::Instance().Name(), &bsp::HseClockSource::Instance());
            _dic.Add(bsp::PllClockSource::Instance().Name(), &bsp::PllClockSource::Instance());
        }

        base::Dictionary<std::string, bsp::IClockSource *> _dic{};
    };

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

base::IDictionary<std::string, bsp::IClockSource *> const &DI_ClockSourceCollection()
{
    Getter g;
    return g.Instance()._dic;
}
