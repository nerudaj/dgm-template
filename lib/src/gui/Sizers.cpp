#include "gui/Sizers.hpp"
#ifdef ANDROID
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
    return 18u;
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
