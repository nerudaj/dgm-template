#pragma once

class Sizers
{
public:
    static [[nodiscard]] unsigned GetSystemDPI();

    static [[nodiscard]] unsigned GetMenuBarHeight();

    static [[nodiscard]] unsigned GetMenuBarTextHeight();

    static [[nodiscard]] unsigned getBaseTextSize()
    {
        return GetMenuBarTextHeight();
    }

    static [[nodiscard]] unsigned getBaseContainerHeight()
    {
        return GetMenuBarHeight();
    }
};
