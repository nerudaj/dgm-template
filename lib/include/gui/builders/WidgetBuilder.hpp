#pragma once

#include "gui/Gui.hpp"
#include "gui/HeadingLevel.hpp"
#include "gui/Sizers.hpp"
#include "misc/Compatibility.hpp"
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <functional>
#include <string>

const tgui::Color PANEL_BACKGROUND_COLOR = tgui::Color(255, 255, 255, 64);

// https://github.com/llvm/llvm-project/issues/36032
struct [[nodiscard]] WidgetOptions final
{
    std::optional<std::string> id = std::nullopt;
    bool enabled = true;
};

// https://github.com/llvm/llvm-project/issues/36032
struct [[nodiscard]] SliderProperties final
{
    std::function<std::string(float)> valueFormatter = [](float val)
    { return std::to_string(val); };
    float low = 0.f;
    float high = 100.f;
    float step = 1.f;
};

class WidgetBuilder final
{
public:
    using Label = std::string;

public:
    static [[nodiscard]] inline tgui::Label::Ptr createTextLabel(
        const std::string& text, const Sizers& sizer, bool justify = false)
    {
        return createLabelInternal(text, 1.f, sizer, justify);
    }

    static [[nodiscard]] inline tgui::Label::Ptr createHeading(
        const std::string& text,
        const Sizers& sizer,
        HeadingLevel level = HeadingLevel::H1)
    {
        return createLabelInternal(
            text, level == HeadingLevel::H1 ? 4.f : 2.f, sizer, true);
    }

    static [[nodiscard]] tgui::Container::Ptr createRow(const Sizers& sizer);

    // Create button with 100% size of the parent (but default font size)
    static [[nodiscard]] tgui::Button::Ptr createButton(
        const Label& label,
        std::function<void(void)> onClick,
        const Sizers& sizer,
        WidgetOptions options = WidgetOptions {});

    // Create a button that can fit inside an option row
    static [[nodiscard]] tgui::Button::Ptr createRowButton(
        const Label& label,
        std::function<void(void)> onClick,
        const Sizers& sizer,
        WidgetOptions options = WidgetOptions {});

    static [[nodiscard]] tgui::CheckBox::Ptr createCheckbox(
        bool checked,
        std::function<void(bool)> onChange,
        WidgetOptions options = {});

    static [[nodiscard]] tgui::Container::Ptr createSlider(
        float value,
        std::function<void(float)> onChange,
        Gui& gui,
        const Sizers& sizer,
        const SliderProperties& properties = {},
        WidgetOptions options = {});

    static [[nodiscard]] tgui::ComboBox::Ptr createDropdown(
        const std::vector<std::string>& items,
        const std::string& selected,
        std::function<void(std::size_t)> onSelect,
        const Sizers& sizer,
        WidgetOptions options = {});

    static [[nodiscard]] tgui::EditBox::Ptr createTextInput(
        const std::string& initialValue,
        std::function<void(tgui::String)> onChange,
        const Sizers& sizer,
        const std::string& regexValidator = "",
        WidgetOptions options = {});

    template<std::integral Number>
    static [[nodiscard]] tgui::EditBox::Ptr createNumericInput(
        Number value,
        std::function<void(Number)> onChange,
        const std::string& validator = getUnsignedNumericValidator(),
        WidgetOptions options = {})
    {
        return createTextInput(
            std::to_string(value),
            [onChange](const tgui::String& newVal)
            {
                auto converted = std::stoul(newVal.toStdString());
                if (converted > std::numeric_limits<Number>::max())
                    throw std::runtime_error(uni::format(
                        "Number is too big to fit {} bytes", sizeof(Number)));
                onChange(static_cast<Number>(converted));
            },
            validator,
            options);
    }

    static [[nodiscard]] tgui::Tabs::Ptr createTabs(
        const std::vector<Label>& tabLabels,
        std::function<void(const tgui::String&)> onTabChange,
        const Sizers& sizer,
        WidgetOptions options = {});

    static [[nodiscard]] tgui::SeparatorLine::Ptr createSeparator();

    static [[nodiscard]] constexpr std::string
    getUnsignedNumericValidator() noexcept
    {
        return "(0|[1-9][0-9]*)";
    }

    static [[nodiscard]] constexpr std::string
    getPositiveNumericValidator() noexcept
    {
        return "[1-9][0-9]*";
    }

private:
    static [[nodiscard]] tgui::Label::Ptr createLabelInternal(
        const std::string& text,
        const float sizeMultiplier,
        const Sizers& sizer,
        const bool justify = false);

    static void
    applyOptionsToWidget(WidgetOptions options, tgui::Widget::Ptr widget)
    {
        if (options.id) widget->setWidgetName(options.id.value());
        widget->setEnabled(options.enabled);
    }

    static void updateDropdownItems(
        tgui::ComboBox::Ptr dropdown, const std::vector<std::string>& items);
};
