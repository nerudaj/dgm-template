#pragma once

#include "misc/Compatibility.hpp"
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <functional>
#include <string>
#include <vector>

class [[nodiscard]] ButtonListBuilder final
{
public:
    ButtonListBuilder() = default;
    ButtonListBuilder(const ButtonListBuilder&) = delete;
    ButtonListBuilder(ButtonListBuilder&&) = delete;
    ~ButtonListBuilder() = default;

public:
    ButtonListBuilder&
    addButton(const std::string& label, std::function<void(void)> onClick);

    NODISCARD_RESULT tgui::Panel::Ptr build();

private:
    struct ButtonProps
    {
        std::string label;
        std::function<void(void)> onClick;
    };

    std::vector<ButtonProps> buttonProps;
};
