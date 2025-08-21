#pragma once

#include "strings/StringProvider.hpp"
#include <DGM/classes/Compatibility.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <string>
#include <tuple>
#include <vector>

// https://github.com/llvm/llvm-project/issues/36032
struct [[nodiscard]] OptionConfig final
{
    bool disabled = false;
    std::optional<std::string> tooltipText = {};
};

class [[nodiscard]] FormBuilder final
{
public:
    FormBuilder(const StringProvider& strings) noexcept : strings(strings) {}

    FormBuilder(const FormBuilder&) = delete;
    FormBuilder(FormBuilder&&) = delete;
    ~FormBuilder() = default;

public:
    FormBuilder& addOption(
        const StringId labelId,
        tgui::Widget::Ptr widget,
        OptionConfig config = {});

    FormBuilder& addOptionWithWidgetId(
        const StringId labelId,
        tgui::Widget::Ptr widget,
        const std::string widgetId);

    FormBuilder& addOptionWithSubmit(
        const StringId labelId,
        tgui::Widget::Ptr widget,
        tgui::Button::Ptr submitBtn);

    FormBuilder& addSeparator();

    NODISCARD_RESULT tgui::Container::Ptr build();

private:
    static NODISCARD_RESULT tgui::Container::Ptr createOptionRow(
        const std::string& labelText,
        tgui::Widget::Ptr widgetPtr,
        std::optional<std::string> widgetId);

    static NODISCARD_RESULT tgui::Container::Ptr
    createOptionRowWithSubmitButton(
        const std::string& labelText,
        tgui::Widget::Ptr widgetPtr,
        tgui::Button::Ptr buttonPtr);

private:
    struct [[nodiscard]] RowProps final
    {
        bool separator = false;
        std::string label;
        tgui::Widget::Ptr widget;
        std::optional<std::string> widgetId = {};
        std::optional<tgui::Button::Ptr> submitBtn = {};
        std::optional<std::string> tooltipText = {};
    };

    const StringProvider& strings;
    std::vector<RowProps> rowsToBuild;
};
