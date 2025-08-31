#pragma once

#include "misc/Compatibility.hpp"
#include "strings/StringProvider.hpp"
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <functional>
#include <string>
#include <vector>

class [[nodiscard]] ButtonListBuilder final
{
public:
    ButtonListBuilder(const StringProvider& strings) noexcept : strings(strings)
    {
    }

    ButtonListBuilder(const ButtonListBuilder&) = delete;
    ButtonListBuilder(ButtonListBuilder&&) = delete;
    ~ButtonListBuilder() = default;

public:
    ButtonListBuilder& addButton(
        const StringId labelId,
        std::function<void(void)> onClick,
        const std::string& buttonId = "");

    NODISCARD_RESULT tgui::Container::Ptr build(
        tgui::HorizontalAlignment alignment =
            tgui::HorizontalAlignment::Center);

private:
    struct ButtonProps
    {
        std::string label;
        std::function<void(void)> onClick;
        std::string buttonId;
    };

    const StringProvider& strings;
    std::vector<ButtonProps> buttonProps;
};
