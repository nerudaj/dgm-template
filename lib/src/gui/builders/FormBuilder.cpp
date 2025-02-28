#include "gui/builders/FormBuilder.hpp"
#include "gui/Sizers.hpp"
#include "gui/builders/WidgetBuilder.hpp"
#include <ranges>

FormBuilder& FormBuilder::addOption(
    const std::string& labelText, tgui::Widget::Ptr widget, OptionConfig config)
{
    widget->setEnabled(!config.disabled);
    rowsToBuild.push_back({ .label = labelText,
                            .widget = widget,
                            .tooltipText = config.tooltipText });
    return *this;
}

FormBuilder& FormBuilder::addOptionWithWidgetId(
    const std::string& labelText,
    tgui::Widget::Ptr widget,
    const std::string widgetId)
{
    rowsToBuild.push_back(
        { .label = labelText, .widget = widget, .widgetId = widgetId });
    return *this;
}

FormBuilder& FormBuilder::addOptionWithSubmit(
    const std::string& labelText,
    tgui::Widget::Ptr widget,
    tgui::Button::Ptr submitBtn)
{
    rowsToBuild.push_back(
        { .label = labelText, .widget = widget, .submitBtn = submitBtn });
    return *this;
}

FormBuilder& FormBuilder::addSeparator()
{
    rowsToBuild.push_back({ .separator = true });
    return *this;
}

tgui::Panel::Ptr FormBuilder::build(tgui::Color backgroundColor)
{
    auto&& panel = WidgetBuilder::createPanel(
        { "100%",
          Sizers::getBaseContainerHeight() * rowsToBuild.size() + 20.f },
        backgroundColor);
    panel->getRenderer()->setPadding({ 10.f, 10.f });

    for (auto&& [idx, props] : std::views::enumerate(rowsToBuild))
    {
        auto&& row =
            props.separator ? WidgetBuilder::createRow()
            : props.submitBtn
                ? createOptionRowWithSubmitButton(
                      props.label, props.widget, props.submitBtn.value())
                : createOptionRow(props.label, props.widget, props.widgetId);
        row->setPosition({ "0%", row->getSize().y * idx });

        if (props.separator)
        {
            row->add(WidgetBuilder::createSeparator());
        }
        else if (props.tooltipText.has_value())
        {
            row->setToolTip(
                WidgetBuilder::createTooltip(props.tooltipText.value()));
        }

        panel->add(row);
    }

    return panel;
}

static tgui::Label::Ptr createRowLabel(const std::string& text)
{
    auto&& label = tgui::Label::create(text);
    label->getRenderer()->setTextColor(sf::Color::Black);
    label->setSize("60%", "100%");
    label->setPosition("0%", "0%");
    label->setTextSize(Sizers::GetMenuBarTextHeight());
    label->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
    return label;
}

tgui::Panel::Ptr FormBuilder::createOptionRow(
    const std::string& labelText,
    tgui::Widget::Ptr widgetPtr,
    std::optional<std::string> widgetId)
{
    auto&& row = WidgetBuilder::createRow();
    row->add(createRowLabel(labelText));

    auto&& widgetPanel = tgui::Panel::create({ "40%", "100%" });
    widgetPanel->setPosition("60%", "0%");
    widgetPanel->getRenderer()->setBackgroundColor(tgui::Color::Transparent);
    row->add(widgetPanel);

    widgetId
        .or_else(
            [&]() -> std::optional<std::string>
            {
                widgetPanel->add(widgetPtr);
                return std::nullopt;
            })
        .and_then(
            [&](auto id) -> std::optional<std::string>
            {
                widgetPanel->add(widgetPtr, id);
                return id;
            });

    return row;
}

tgui::Panel::Ptr FormBuilder::createOptionRowWithSubmitButton(
    const std::string& labelText,
    tgui::Widget::Ptr widgetPtr,
    tgui::Button::Ptr buttonPtr)
{
    auto&& row = WidgetBuilder::createRow();
    row->add(createRowLabel(labelText));

    auto&& widgetPanel = tgui::Panel::create({ "25%", "100%" });
    widgetPanel->setPosition("60%", "0%");
    widgetPanel->getRenderer()->setBackgroundColor(tgui::Color::Transparent);
    widgetPanel->add(widgetPtr);
    row->add(widgetPanel);

    auto&& btnPanel = tgui::Panel::create({ "15%", "100%" });
    btnPanel->setPosition("85%", "0%");
    btnPanel->getRenderer()->setBackgroundColor(tgui::Color::Transparent);
    btnPanel->add(buttonPtr);
    row->add(btnPanel);

    return row;
}