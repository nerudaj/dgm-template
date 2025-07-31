#include "gui/builders/TabbedLayoutBuilder.hpp"
#include "gui/Sizers.hpp"
#include "gui/builders/NavbarLayoutBuilder.hpp"
#include "gui/builders/WidgetBuilder.hpp"

TabbedLayoutBuilder& TabbedLayoutBuilder::addTab(
    const std::string& tabName,
    const std::function<void(tgui::Container::Ptr)> onTabSelected)
{
    tabNames.push_back(tabName);
    tabCallbacks[tabName] = onTabSelected;
    return *this;
}

TabbedLayoutBuilder&
TabbedLayoutBuilder::setTabSelected(const std::string& tabName)
{
    selectedTab = tabName;
    return *this;
}

tgui::Container::Ptr
TabbedLayoutBuilder::build(const TabbedLayoutOptions& options)
{
    auto content = createContentPanel(options.contentIsScrollable);
    auto tabs = WidgetBuilder::createTabs(
        tabNames,
        [tabNames = tabNames,
         callbacks = std::move(tabCallbacks),
         content = content](const tgui::String& tabName)
        {
            for (auto&& name : tabNames)
            {
                if (name == tabName)
                {
                    callbacks.at(name)(content);
                }
            }
        },
        WidgetOptions {
            .id = options.tabsWidgetId,
        });
    tabs->select(selectedTab);

    return NavbarLayoutBuilder()
        .withNavbarWidget(tabs)
        .withContent(content, options.contentWidgetId)
        .build();
}

tgui::Container::Ptr
TabbedLayoutBuilder::createContentPanel(bool isScrollable) const
{
    if (isScrollable)
    {
        return tgui::ScrollablePanel::create({ "100%", "100%" });
    }
    return tgui::Panel::create({ "100%", "100%" });
}
