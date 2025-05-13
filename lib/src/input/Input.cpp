#include "input/Input.hpp"

Input::Input()
{
    controller.bindInput(InputKind::BackButton, sf::Keyboard::Key::Escape);

    controller.bindInput(InputKind::Left, sf::Keyboard::Key::A);
    controller.bindInput(InputKind::Right, sf::Keyboard::Key::D);
    controller.bindInput(InputKind::Jump, sf::Keyboard::Key::Space);

    try
    {
        const auto id = sf::Joystick::getIdentification(0);

        controller.bindInput(
            InputKind::BackButton,
            dgm::translateGamepadCode(dgm::GamepadCode::Select, id));

        controller.bindInput(
            InputKind::ConfirmButton,
            dgm::translateGamepadCode(dgm::GamepadCode::A, id));

        controller.bindInput(
            InputKind::CursorUp,
            dgm::translateGamepadCode(dgm::GamepadCode::LStickUp, id));
        controller.bindInput(
            InputKind::CursorDown,
            dgm::translateGamepadCode(dgm::GamepadCode::LStickDown, id));
        controller.bindInput(
            InputKind::CursorLeft,
            dgm::translateGamepadCode(dgm::GamepadCode::LStickLeft, id));
        controller.bindInput(
            InputKind::CursorRight,
            dgm::translateGamepadCode(dgm::GamepadCode::LStickRight, id));

        controller.bindInput(
            InputKind::MenuCycleLeft,
            dgm::translateGamepadCode(dgm::GamepadCode::LBumper, id));

        controller.bindInput(
            InputKind::MenuCycleRight,
            dgm::translateGamepadCode(dgm::GamepadCode::RBumper, id));
    }
    catch (...)
    {
        controller.bindInput(InputKind::ConfirmButton, 0);
        controller.bindInput(InputKind::BackButton, 10);
        controller.bindInput(
            InputKind::CursorLeft,
            sf::Joystick::Axis::X,
            dgm::AxisHalf::Negative);
        controller.bindInput(
            InputKind::CursorRight,
            sf::Joystick::Axis::X,
            dgm::AxisHalf::Positive);
        controller.bindInput(
            InputKind::CursorUp,
            sf::Joystick::Axis::Y,
            dgm::AxisHalf::Negative);
        controller.bindInput(
            InputKind::CursorDown,
            sf::Joystick::Axis::Y,
            dgm::AxisHalf::Positive);
    }
}

float Input::getHorizontalVelocity() const
{
    return -controller.readAnalog(InputKind::Left)
           + controller.readAnalog(InputKind::Right);
}

bool Input::isJumpPressed() const
{
    return controller.readDigital(InputKind::Jump);
}

NODISCARD_RESULT bool Input::isMenuCycleLeftPressed() const
{
    return readAndRelease(InputKind::MenuCycleLeft);
}

NODISCARD_RESULT bool Input::isMenuCycleRightPressed() const
{
    return readAndRelease(InputKind::MenuCycleRight);
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
        controller.readAnalog(InputKind::CursorLeft)
            + controller.readAnalog(InputKind::CursorRight),
        controller.readAnalog(InputKind::CursorUp)
            + controller.readAnalog(InputKind::CursorDown),
    };
}

bool Input::readAndRelease(InputKind i) const
{
    return controller.readDigital(i, dgm::DigitalReadKind::OnPress);
}
