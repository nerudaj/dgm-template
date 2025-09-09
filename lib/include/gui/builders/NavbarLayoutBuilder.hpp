#pragma once

#include "gui/Sizers.hpp"
#include "misc/Compatibility.hpp"
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <optional>

namespace priv
{
    class [[nodiscard]] FinalNavbarLayoutBuilder final
    {
    public:
        FinalNavbarLayoutBuilder(
            tgui::Widget::Ptr widget,
            tgui::Container::Ptr content,
            const std::optional<std::string>& contentPanelId,
            const Sizers& sizer)
            : widget(widget)
            , content(content)
            , contentPanelId(contentPanelId)
            , sizer(sizer) {};
        FinalNavbarLayoutBuilder(const FinalNavbarLayoutBuilder&) = delete;
        FinalNavbarLayoutBuilder(FinalNavbarLayoutBuilder&&) = delete;
        ~FinalNavbarLayoutBuilder() = default;

    public:
        [[nodiscard]] tgui::Container::Ptr build();

    private:
        tgui::Widget::Ptr widget;
        tgui::Container::Ptr content;
        const std::optional<std::string>& contentPanelId;
        const Sizers& sizer;
    };

    class [[nodiscard]] NavbarLayoutWithNavbarWidgetBuilder final
    {
    public:
        NavbarLayoutWithNavbarWidgetBuilder(
            tgui::Widget::Ptr widget, const Sizers& sizer)
            : widget(widget), sizer(sizer) {};
        NavbarLayoutWithNavbarWidgetBuilder(
            const NavbarLayoutWithNavbarWidgetBuilder&) = delete;
        NavbarLayoutWithNavbarWidgetBuilder(
            NavbarLayoutWithNavbarWidgetBuilder&&) = delete;
        ~NavbarLayoutWithNavbarWidgetBuilder() = default;

    public:
        FinalNavbarLayoutBuilder withContent(
            tgui::Container::Ptr content,
            const std::optional<std::string>& contentPanelId = std::nullopt)
        {
            return FinalNavbarLayoutBuilder(
                widget, content, contentPanelId, sizer);
        }

    private:
        tgui::Widget::Ptr widget;
        const Sizers& sizer;
    };
} // namespace priv

class [[nodiscard]] NavbarLayoutBuilder final
{
public:
    constexpr explicit NavbarLayoutBuilder(const Sizers& sizer) noexcept
        : sizer(sizer)
    {
    }

    NavbarLayoutBuilder(const NavbarLayoutBuilder&) = delete;
    NavbarLayoutBuilder(NavbarLayoutBuilder&&) = delete;
    ~NavbarLayoutBuilder() = default;

public:
    priv::NavbarLayoutWithNavbarWidgetBuilder
    withNavbarWidget(tgui::Widget::Ptr widget)
    {
        return priv::NavbarLayoutWithNavbarWidgetBuilder(widget, sizer);
    }

private:
    const Sizers& sizer;
};
