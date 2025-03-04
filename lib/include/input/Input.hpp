#pragma once

#include <DGM/dgm.hpp>

enum class [[nodiscard]] InputKind
{
    BackButton,
    ConfirmButton,
    CursorUp,
    CursorDown,
    CursorLeft,
    CursorRight,
    Left,
    Right,
    Jump,
};

class [[nodiscard]] Input final
{
public:
    Input();
    Input(Input&&) = delete;
    Input(const Input&) = delete;

public:
    void update()
    {
        controller.update();
    }

#pragma region For dummy entity, can be removed
    float getHorizontalVelocity() const;

    [[nodiscard]] bool isJumpPressed() const;
#pragma endregion

    [[nodiscard]] bool isBackButtonPressed() const;

    [[nodiscard]] bool isConfirmPressed() const;

    [[nodiscard]] sf::Vector2f getCursorDelta() const;

private:
    bool readAndRelease(InputKind i) const;

private:
    mutable dgm::Controller controller;
};
