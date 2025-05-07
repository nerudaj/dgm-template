#include "gui/Sizers.hpp"

#ifdef ANDROID

#include <jni/Resources.hpp>

/**
 * Lazy-initialized base-size provider for Android.
 */
struct [[nodiscard]] BaseSizeProviderSingleton final
{
private:
    BaseSizeProviderSingleton()
    {
        // TODO: get activity states

        auto core = Core::attachCurrentThread(vm, env);

        auto resources = jni::Resources::getSystem(env);
        baseSize = spToPx(
            14,
            resources.GetDisplayMetrics().getDensity());
    }

public:
    BaseSizeProviderSingleton(BaseSizeProviderSingleton&&) = delete;
    BaseSizeProviderSingleton(const BaseSizeProviderSingleton&) = delete;

public:
    BaseSizeProviderSingleton& getInstance()
    {
        static BaseSizeProviderSingleton instance;
        return instance;
    }

    [[nodiscard]] unsigned getBaseFontSize() const noexcept
    {
        return baseSize;
    }

private:
    unsigned spToPx(unsigned sp, float density)
    {
        return static_cast<unsigned>(sp * density);
    }

private:
    unsigned baseSize = 0;
};

unsigned Sizers::GetSystemDPI()
{
    return 1u;
}

unsigned Sizers::GetMenuBarHeight()
{
    return 22u;
}

unsigned Sizers::GetMenuBarTextHeight()
{
    return BaseSizeProviderSingleton::getInstance().getBaseFontSize();
}
#else
#include <Windows.h>

unsigned Sizers::GetSystemDPI()
{
    return GetDpiForSystem();
}

unsigned Sizers::GetMenuBarHeight()
{
    const unsigned dpi = GetSystemDPI();
    return GetSystemMetricsForDpi(SM_CYCAPTION, dpi)
           + GetSystemMetricsForDpi(SM_CYSIZEFRAME, dpi)
           + GetSystemMetricsForDpi(SM_CYEDGE, dpi) * 2;
}

unsigned Sizers::GetMenuBarTextHeight()
{
    return static_cast<unsigned>(GetMenuBarHeight() / 2.55f);
}
#endif
