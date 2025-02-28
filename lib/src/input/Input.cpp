#include "input/Input.hpp"

Input::Input()
{
    controller.bindInput(
        std::to_underlying(InputKind::BackButton), sf::Keyboard::Key::Escape);
    controller.bindInput(
        std::to_underlying(InputKind::BackButton), dgm::Xbox::Button::Back);

    controller.bindInput(
        std::to_underlying(InputKind::ConfirmButton), dgm::Xbox::Button::A);

    controller.bindInput(
        std::to_underlying(InputKind::CursorUp), dgm::Xbox::Axis::LStickYneg);
    controller.bindInput(
        std::to_underlying(InputKind::CursorDown), dgm::Xbox::Axis::LStickYpos);
    controller.bindInput(
        std::to_underlying(InputKind::CursorLeft), dgm::Xbox::Axis::LStickXneg);
    controller.bindInput(
        std::to_underlying(InputKind::CursorRight),
        dgm::Xbox::Axis::LStickXpos);
}

bool Input::isBackButtonPressed() const
{
    return readAndRelease(InputKind::BackButton);
}

bool Input::isConfirmPressed() const
{
    return readAndRelease(InputKind::ConfirmButton);
}

sf::Vector2f Input::getCursorDelta() const
{
    return sf::Vector2f {
        controller.getInputValue(std::to_underlying(InputKind::CursorLeft))
            + controller.getInputValue(
                std::to_underlying(InputKind::CursorRight)),
        controller.getInputValue(std::to_underlying(InputKind::CursorUp))
            + controller.getInputValue(
                std::to_underlying(InputKind::CursorDown)),
    };
}

bool Input::readAndRelease(InputKind i) const
{
    const bool value = controller.isInputToggled(std::to_underlying(i));
    if (value) controller.releaseInput(std::to_underlying(i));
    return value;
}
