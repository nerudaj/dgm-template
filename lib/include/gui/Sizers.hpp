#pragma once

class Sizers
{
public:
    static unsigned GetSystemDPI();

    static unsigned GetMenuBarHeight();

    static unsigned GetMenuBarTextHeight();

    static unsigned getBaseTextSize()
    {
        return GetMenuBarTextHeight();
    }

    static unsigned getBaseContainerHeight()
    {
        return GetMenuBarHeight();
    }
};
