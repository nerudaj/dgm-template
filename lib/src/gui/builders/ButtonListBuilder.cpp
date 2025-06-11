#include "gui/builders/ButtonListBuilder.hpp"
#include "gui/Sizers.hpp"
#include "gui/builders/WidgetBuilder.hpp"
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <ranges>

ButtonListBuilder& ButtonListBuilder::addButton(
    const std::string& label,
    std::function<void(void)> onClick,
    const std::string& buttonId)
{
    buttonProps.emplace_back(label, onClick, buttonId);
    return *this;
}

tgui::Container::Ptr ButtonListBuilder::build()
{
    auto&& outerPanel = WidgetBuilder::createScrollablePanel();
    auto&& layout = tgui::GrowVerticalLayout::create();
    layout->getRenderer()->setSpaceBetweenWidgets(
        Sizers::getBaseContainerHeight() * 0.1f);

    // TODO: this and both horizontal and vertical alignment
    layout->setWidth({ "20%" });

    outerPanel->add(layout);

    for (auto&& [idx, props] : std::views::enumerate(buttonProps))
    {
        auto&& button = WidgetBuilder::createButton(props.label, props.onClick);
        button->setSize({ "100%", Sizers::getBaseContainerHeight() * 1.5f });
        button->setTextSize(Sizers::getBaseFontSize() * 2u);

        layout->add(button, props.buttonId);
    }

    return outerPanel;
}