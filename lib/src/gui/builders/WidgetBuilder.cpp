#include "gui/builders/WidgetBuilder.hpp"
#include "gui/Sizers.hpp"
#include "gui/TguiHelper.hpp"
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <ranges>

NODISCARD_RESULT std::string randomString(std::size_t len)
{
    constexpr auto CHARS = std::string_view(
        "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    return std::views::iota(0u, len)
           | std::views::transform([CHARS](std::size_t)
                                   { return CHARS[rand() % CHARS.size()]; })
           | std::ranges::to<std::string>();
}

tgui::Label::Ptr WidgetBuilder::createLabelInternal(
    const std::string& text, const float sizeMultiplier, const bool justify)
{
    auto&& label = tgui::Label::create(text);
    label->getRenderer()->setTextColor(sf::Color::White);
    label->getRenderer()->setTextOutlineColor(tgui::Color::Black);
    label->getRenderer()->setTextOutlineThickness(1.f);
    label->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
    label->setHorizontalAlignment(
        justify ? tgui::Label::HorizontalAlignment::Center
                : tgui::Label::HorizontalAlignment::Left);
    label->setTextSize(
        static_cast<unsigned>(Sizers::getBaseTextSize() * sizeMultiplier));
    label->setSize({ "100%", "100%" });
    return label;
}

tgui::Panel::Ptr
WidgetBuilder::createPanel(const tgui::Layout2d& size, const tgui::Color color)
{
    auto&& panel = tgui::Panel::create(size);
    panel->setPosition({ "0%", "0%" });
    panel->getRenderer()->setBackgroundColor(color);
    return panel;
}

tgui::Panel::Ptr WidgetBuilder::createRow(tgui::Color bgcolor)
{
    auto&& row = tgui::Panel::create();
    row->setSize("100%", std::to_string(Sizers::GetMenuBarHeight()).c_str());
    row->getRenderer()->setBackgroundColor(bgcolor);
    return row;
}

tgui::Button::Ptr WidgetBuilder::createButton(
    const Label& label,
    std::function<void(void)> onClick,
    WidgetOptions options)
{
    auto&& button = tgui::Button::create(label);
    button->onClick(onClick);
    button->setTextSize(Sizers::getBaseTextSize());
    button->setSize({ "100%", "100%" });

    applyOptionsToWidget(options, button);

    return button;
}

tgui::CheckBox::Ptr WidgetBuilder::createCheckbox(
    bool checked, std::function<void(bool)> onChange, WidgetOptions options)
{
    auto&& checkbox = tgui::CheckBox::create();
    auto&& size = checkbox->getSizeLayout();
    checkbox->setPosition(("100%" - size.x) / 2, ("100%" - size.y) / 2);
    checkbox->setChecked(checked);
    checkbox->onChange(onChange);

    applyOptionsToWidget(options, checkbox);

    return checkbox;
}

tgui::Panel::Ptr WidgetBuilder::createSlider(
    float value,
    std::function<void(float)> onChange,
    Gui& gui,
    const SliderProperties& properties,
    WidgetOptions options)
{
    auto&& result = tgui::Panel::create();
    result->getRenderer()->setBackgroundColor(tgui::Color::Transparent);
    const auto&& ID = randomString(16);

    auto&& dummyLabel = tgui::Label::create(
        properties.valueFormatter(properties.high + properties.step));
    dummyLabel->setTextSize(Sizers::GetMenuBarTextHeight());
    dummyLabel->setAutoSize(true);
    gui.add(dummyLabel, "DummyLabel");
    auto size = dummyLabel->getSizeLayout();

    auto&& valueLabel = tgui::Label::create(properties.valueFormatter(value));
    valueLabel->setTextSize(Sizers::GetMenuBarTextHeight());
    valueLabel->getRenderer()->setTextColor(sf::Color::Black);
    valueLabel->setSize(size.x, "100%");
    valueLabel->setPosition("parent.width" - size.x, "0%");
    valueLabel->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
    valueLabel->setHorizontalAlignment(
        tgui::Label::HorizontalAlignment::Center);
    result->add(valueLabel, ID);

    auto&& slider = tgui::Slider::create(properties.low, properties.high);
    slider->setPosition("2%", "25%");
    slider->setSize("parent.width - 4% - " - size.x, "50%");
    slider->setStep(properties.step);
    slider->setValue(value);
    slider->onValueChange(
        [&gui,
         ID,
         onChange,
         valueFormatter = std::move(properties.valueFormatter)](float value)
        {
            gui.get<tgui::Label>(ID)->setText(valueFormatter(value));
            onChange(value);
        });

    applyOptionsToWidget(options, slider);

    result->add(slider);

    gui.remove(gui.get<tgui::Label>("DummyLabel"));

    return result;
}

tgui::ComboBox::Ptr WidgetBuilder::createDropdown(
    const std::vector<std::string>& items,
    const std::string& selected,
    std::function<void(std::size_t)> onSelect,
    WidgetOptions options)
{
    auto&& dropdown = tgui::ComboBox::create();
    dropdown->setSize("100%", "80%");
    dropdown->setPosition("0%", "10%");
    updateDropdownItems(dropdown, items);
    dropdown->setSelectedItem(selected);
    dropdown->onItemSelect(onSelect);

    applyOptionsToWidget(options, dropdown);

    return dropdown;
}

tgui::EditBox::Ptr WidgetBuilder::createTextInput(
    const std::string& initialValue,
    std::function<void(tgui::String)> onChange,
    const std::string& regexValidator,
    WidgetOptions options)
{
    auto&& box = tgui::EditBox::create();
    box->setSize("100%", "80%");
    box->setPosition("0%", "10%");
    if (!regexValidator.empty()) box->setInputValidator(regexValidator);
    box->setText(initialValue);
    box->onTextChange(onChange);

    applyOptionsToWidget(options, box);

    return box;
}

tgui::Tabs::Ptr WidgetBuilder::createTabbedContent(
    const std::vector<Label>& tabLabels,
    std::function<void(const tgui::String&)> onTabChange,
    WidgetOptions options)
{
    auto&& tabs = tgui::Tabs::create();
    tabs->setSize({ "100%", "100%" });
    tabs->setTextSize(Sizers::getBaseTextSize());

    for (auto&& label : tabLabels)
    {
        tabs->add(label);
    }

    tabs->select(tabLabels.front());
    tabs->onTabSelect(onTabChange);

    applyOptionsToWidget(options, tabs);

    return tabs;
}

tgui::SeparatorLine::Ptr WidgetBuilder::createSeparator()
{
    auto sep = tgui::SeparatorLine::create({ "100%", 1 });
    sep->setPosition({ "0%", "49%" });
    return sep;
}

tgui::Label::Ptr WidgetBuilder::createTooltip(const std::string& text)
{
    auto label = tgui::Label::create(text);
    label->getRenderer()->setBackgroundColor(sf::Color::White);
    label->getRenderer()->setBorders(tgui::Borders::Outline(1));
    label->getRenderer()->setBorderColor(sf::Color::Black);
    label->setTextSize(Sizers::getBaseTextSize());
    return label;
}

void WidgetBuilder::updateDropdownItems(
    tgui::ComboBox::Ptr dropdown, const std::vector<std::string>& items)
{
    dropdown->removeAllItems();
    for (auto&& item : items)
    {
        dropdown->addItem(item, item);
    }
    dropdown->setSelectedItem(items.front());
}