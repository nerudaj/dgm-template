#include "input/TouchController.hpp"
#include <DGM/classes/Collision.hpp>
#include <DGM/classes/Math.hpp>

TouchModel::TouchModel(const sf::Vector2u& windowSize)
    : objects(std::array {
          TouchObject {
              .touchArea = dgm::Circle({ 100.f, windowSize.y - 100.f }, 100.f),
              .touchPosition = { 100.f, 100.f },
              .kind = TouchObjectKind::Joystick,
          },
          TouchObject {
              .touchArea = dgm::Circle(
                  { windowSize.x - 100.f, windowSize.y - 100.f }, 100.f),
              .touchPosition = sf::Vector2f {},
              .kind = TouchObjectKind::Joystick,
          } })
{
}

void TouchController::processEvent(const std::optional<sf::Event>& e)
{
    if (e->is<sf::Event::TouchBegan>())
        processEvent(e->getIf<sf::Event::TouchBegan>());
    else if (e->is<sf::Event::TouchEnded>())
        processEvent(e->getIf<sf::Event::TouchEnded>());
    else if (e->is<sf::Event::TouchMoved>())
        processEvent(e->getIf<sf::Event::TouchMoved>());
}

NODISCARD_RESULT float TouchController::getHorizontalVelocity() const
{
    return (model.leftJoystick.touchPosition
            - model.leftJoystick.touchArea.getPosition())
        .x;
}

NODISCARD_RESULT bool TouchController::isJumpPressed() const
{
    return dgm::Collision::basic(
        model.jumpButton.touchArea,
        sf::Vector2i(model.jumpButton.touchPosition));
}

void TouchController::processEvent(const sf::Event::TouchBegan& e)
{
    for (auto&& [idx, object] : std::ranges::views::enumerate(model.objects))
    {
        if (dgm::Collision::basic(object.touchArea, e.position))
        {
            object.touchPosition = sf::Vector2f(e.position);
            model.fingerToTouchObject[e.finger] = idx;
        }
    }
}

void TouchController::processEvent(const sf::Event::TouchEnded& e)
{
    auto idx = model.fingerToTouchObject[e.finger];
    model.fingerToTouchObject.erase(e.finger);

    if (model.objects[idx].kind == TouchObjectKind::Button)
    {
        // place touch position outside of button
        model.objects[idx].touchPosition =
            model.objects[idx].touchArea.getPosition()
            + sf::Vector2f(1.f, 0) * model.objects[idx].touchArea.getRadius()
                  * 2.f;
    }
    else
    {
        // Center joystick hat
        model.objects[idx].touchPosition =
            model.objects[idx].touchArea.getPosition();
    }
}

void TouchController::processEvent(const sf::Event::TouchMoved& e)
{
    // Update touchPosition, but normalize it so it stays inside the touchArea
    // even when the finger moves out of it

    auto idx = model.fingerToTouchObject[e.finger];
    auto& obj = model.objects[idx];
    auto direction = sf::Vector2f(e.position) - obj.touchArea.getPosition();
    auto length = direction.length();
    obj.touchPosition = dgm::Math::toUnit(direction)
                        * std::clamp(length, 0.f, obj.touchArea.getRadius());
}
