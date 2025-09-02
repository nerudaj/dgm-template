#include "input/TouchController.hpp"

void TouchInput::reset()
{
    if (kind == TouchObjectKind::Button)
        // place touch position out of touchArea - button is not pressed
        touchPosition = touchArea.getPosition()
                        - sf::Vector2f {
                              touchArea.getRadius(),
                              touchArea.getRadius(),
                          };
    else
        touchPosition = touchArea.getPosition();
}

TouchModel::TouchModel(const sf::Vector2u& windowSize)
    : objects(std::array {
          TouchInput(
              TouchObjectKind::Joystick,
              { 100.f, windowSize.y - 100.f },
              100.f),
          TouchInput(
              TouchObjectKind::Button,
              { windowSize.x - 200.f, windowSize.y - 100.f },
              50.f),
      })
{
}

void TouchController::processEvent(const std::optional<sf::Event>& e)
{
    if (e->is<sf::Event::TouchBegan>())
        processEvent(*e->getIf<sf::Event::TouchBegan>());
    else if (e->is<sf::Event::TouchEnded>())
        processEvent(*e->getIf<sf::Event::TouchEnded>());
    else if (e->is<sf::Event::TouchMoved>())
        processEvent(*e->getIf<sf::Event::TouchMoved>());
}

NODISCARD_RESULT float TouchController::getHorizontalVelocity() const
{
    return model.leftJoystick.readJoystick().x;
}

NODISCARD_RESULT bool TouchController::isJumpPressed() const
{
    return model.jumpButton.readButton();
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
    model.objects[idx].reset();
}

void TouchController::processEvent(const sf::Event::TouchMoved& e)
{
    // Update touchPosition, but normalize it so it stays inside the touchArea
    // even when the finger moves out of it

    auto idx = model.fingerToTouchObject[e.finger];
    auto& obj = model.objects[idx];
    auto direction = sf::Vector2f(e.position) - obj.touchArea.getPosition();
    auto length = direction.length();
    obj.touchPosition =
        obj.touchArea.getPosition()
        + dgm::Math::toUnit(direction)
              * std::clamp(length, 0.f, obj.touchArea.getRadius());
}
