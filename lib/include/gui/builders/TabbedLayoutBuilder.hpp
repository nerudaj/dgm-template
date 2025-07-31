#pragma once

#include "misc/Compatibility.hpp"
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <functional>
#include <optional>

struct [[nodiscard]] TabbedLayoutOptions final
{
    std::optional<std::string> tabsWidgetId = std::nullopt;
    std::optional<std::string> contentWidgetId = std::nullopt;
    bool contentIsScrollable = false;
};

/**
 * Builder for creating a list of tabs and a content panel
 * which changes every time a tab is selected.
 *
 * Internally uses NavbarLayoutBuilder, therefore the tabs
 * are placed atop of the container..
 */
class [[nodiscard]] TabbedLayoutBuilder final
{
public:
    TabbedLayoutBuilder& addTab(
        const std::string& tabName,
        const std::function<void(tgui::Container::Ptr)> onTabSelected);

    TabbedLayoutBuilder& setTabSelected(const std::string& tabName);

    NODISCARD_RESULT tgui::Container::Ptr
    build(const TabbedLayoutOptions& options = {});

private:
    NODISCARD_RESULT tgui::Container::Ptr
    createContentPanel(bool isScrollable) const;

private:
    std::vector<std::string> tabNames;
    std::map<std::string, std::function<void(tgui::Container::Ptr)>>
        tabCallbacks;
    std::string selectedTab;
};
