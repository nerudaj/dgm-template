#pragma once

#include <DGM/classes/Controller.hpp>
#include <DGM/classes/Objects.hpp>
#include <SFML/Window/Event.hpp>
#include <input/InputKind.hpp>
#include <misc/Compatibility.hpp>
#include <optional>

enum class TouchObjectKind
{
    Button,
    Joystick
};

struct TouchObject
{
    dgm::Circle touchArea;
    sf::Vector2f touchPosition;
    TouchObjectKind kind;
};

struct TouchModel
{
public:
    TouchModel(const sf::Vector2u& windowSize);

public:
    std::array<TouchObject, 2u> objects;
    std::map<unsigned, size_t> fingerToTouchObject = {};

    TouchObject& leftJoystick = objects[0];
    TouchObject& jumpButton = objects[1];
};

class [[nodiscard]] TouchController final
{
public:
    TouchController(const sf::Vector2u& windowSize) : model(windowSize) {}

public:
    void processEvent(const std::optional<sf::Event>& e);

    CONSTEXPR_NODISCARD const TouchModel& getTouchModel() const noexcept
    {
        return model;
    }

#pragma region For dummy entity, can be removed

    NODISCARD_RESULT float getHorizontalVelocity() const;

    NODISCARD_RESULT bool isJumpPressed() const;

#pragma endregion

private:
    void processEvent(const sf::Event::TouchBegan& e);

    void processEvent(const sf::Event::TouchEnded& e);

    void processEvent(const sf::Event::TouchMoved& e);

private:
    TouchModel model;
};
