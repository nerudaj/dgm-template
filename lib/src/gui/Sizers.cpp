#include "gui/Sizers.hpp"

#ifdef ANDROID

#include <jni/Jni.hpp>

/**
 * Lazy-initialized base-size provider for Android.
 */
struct [[nodiscard]] BaseSizeProviderSingleton final
{
private:
    BaseSizeProviderSingleton()
    {
        auto core = jni::Core::attachCurrentThread(activity.vm, &activity.env);
        auto resources = jni::Resources::getSystem(core.getEnv());
        pixelDensity = resources.GetDisplayMetrics().getDensity();
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
        return spToPx(14, pixelDensity);
    }

    [[nodiscard]] unsigned getBaseContainerHeight() const noexcept
    {
        return spToPx(22, pixelDensity);
    }

private:
    unsigned spToPx(unsigned sp, float density)
    {
        return static_cast<unsigned>(sp * density);
    }

private:
    float pixelDensity = 0.f;
};

unsigned Sizers::getBaseContainerHeight()
{
    return BaseSizeProviderSingleton::getInstance().getBaseContainerHeight();
}

unsigned Sizers::getBaseFontSize()
{
    return BaseSizeProviderSingleton::getInstance().getBaseFontSize();
}
#else
#include <Windows.h>

unsigned Sizers::getBaseContainerHeight()
{
    const unsigned dpi = GetDpiForSystem();
    return GetSystemMetricsForDpi(SM_CYCAPTION, dpi)
           + GetSystemMetricsForDpi(SM_CYSIZEFRAME, dpi)
           + GetSystemMetricsForDpi(SM_CYEDGE, dpi) * 2;
}

unsigned Sizers::getBaseFontSize()
{
    return static_cast<unsigned>(getBaseContainerHeight() / 2.55f);
}
#endif
