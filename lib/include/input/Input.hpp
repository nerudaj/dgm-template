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

    [[nodiscard]] bool isBackButtonPressed() const;

    [[nodiscard]] bool isConfirmPressed() const;

    [[nodiscard]] sf::Vector2f getCursorDelta() const;

private:
    bool readAndRelease(InputKind i) const;

private:
    mutable dgm::Controller controller;
};
