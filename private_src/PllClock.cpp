#include "PllClock.h"

bsp::PllClock &bsp::PllClock::Instance()
{
    class Getter :
        public base::SingletonGetter<PllClock>
    {
    public:
        std::unique_ptr<PllClock> Create() override
        {
            return std::unique_ptr<PllClock>{new PllClock{}};
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
    return g.Instance();
}

std::string bsp::PllClock::Name() const
{
    return "pll";
}

void bsp::PllClock::Open(std::string const &input_channel_name, base::IDictionary<std::string, int> const &factors)
{
#pragma region m,n,p,q,r
    int m = 1;

    {
        int const *ptr = factors.Find("m");
        if (ptr != nullptr)
        {
            m = *ptr;
        }
    }

    int n = 1;

    {
        int const *ptr = factors.Find("n");
        if (ptr != nullptr)
        {
            n = *ptr;
        }
    }

    int p = 1;

    {
        int const *ptr = factors.Find("p");
        if (ptr != nullptr)
        {
            p = *ptr;
        }
    }

    int q = 1;

    {
        int const *ptr = factors.Find("q");
        if (ptr != nullptr)
        {
            q = *ptr;
        }
    }

    int r = 1;

    {
        int const *ptr = factors.Find("r");
        if (ptr != nullptr)
        {
            r = *ptr;
        }
    }
#pragma endregion

#pragma region pll_source
    uint32_t pll_source = RCC_PLLSOURCE_HSE;
    if (input_channel_name == "hse")
    {
        pll_source = RCC_PLLSOURCE_HSE;
    }
    else if (input_channel_name == "hsi")
    {
        pll_source = RCC_PLLSOURCE_HSI;
    }
    else if (input_channel_name == "csi")
    {
        pll_source = RCC_PLLSOURCE_CSI;
    }
    else
    {
        throw std::invalid_argument{"不支持该输入通道"};
    }
#pragma endregion

    RCC_OscInitTypeDef def{};
    def.OscillatorType = RCC_OSCILLATORTYPE_NONE;
    def.PLL.PLLState = RCC_PLL_ON;
    def.PLL.PLLSource = pll_source;
    def.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
    def.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
    def.PLL.PLLM = m;
    def.PLL.PLLN = n;
    def.PLL.PLLP = p;
    def.PLL.PLLQ = q;
    def.PLL.PLLR = r;

    HAL_StatusTypeDef result = HAL_RCC_OscConfig(&def);
    if (result != HAL_StatusTypeDef::HAL_OK)
    {
        throw std::runtime_error{"打开 PLL 失败。"};
    }
}

void bsp::PllClock::Close()
{
    RCC_OscInitTypeDef def{};
    def.OscillatorType = RCC_OSCILLATORTYPE_NONE;
    def.PLL.PLLState = RCC_PLL_OFF;
    HAL_StatusTypeDef result = HAL_RCC_OscConfig(&def);
    if (result != HAL_StatusTypeDef::HAL_OK)
    {
        throw std::runtime_error{"关闭 PLL 失败。"};
    }
}

bsp::IClockSource_State bsp::PllClock::State() const
{
    return _state;
}

base::Hz bsp::PllClock::Frequency(std::string const &output_channel_name) const
{
    return base::Hz();
}
