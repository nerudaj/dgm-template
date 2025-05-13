#pragma once

#include "misc/Compatibility.hpp"
#include <DGM/dgm.hpp>

enum class [[nodiscard]] InputKind
{
    BackButton,
    ConfirmButton,
    CursorUp,
    CursorDown,
    CursorLeft,
    CursorRight,
    MenuCycleLeft,
    MenuCycleRight,
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
#pragma region For dummy entity, can be removed
    float getHorizontalVelocity() const;

    NODISCARD_RESULT bool isJumpPressed() const;
#pragma endregion

    NODISCARD_RESULT bool isMenuCycleLeftPressed() const;

    NODISCARD_RESULT bool isMenuCycleRightPressed() const;

    NODISCARD_RESULT bool isBackButtonPressed() const;

    NODISCARD_RESULT bool isConfirmPressed() const;

    NODISCARD_RESULT sf::Vector2f getCursorDelta() const;

private:
    bool readAndRelease(InputKind i) const;

private:
    mutable dgm::Controller<InputKind> controller;
};
