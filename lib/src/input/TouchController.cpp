#include "input/TouchController.hpp"
#include <SFML/System/Err.hpp>

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

std::array<TouchInput, 3u>
TouchModel::computeLayout(const sf::Vector2u& windowSize)
{
    const float windowWidth10perc = windowSize.x * 0.1f;
    const float windowWidth5perc = windowSize.x * 0.05f;

    return std::array {
        TouchInput(
            TouchObjectKind::Joystick,
            { windowWidth10perc, windowSize.y - windowWidth10perc },
            windowWidth10perc),
        TouchInput(
            TouchObjectKind::Button,
            { windowSize.x - windowWidth10perc,
              windowSize.y - windowWidth10perc },
            windowWidth10perc),
        TouchInput(
            TouchObjectKind::Button,
            { windowWidth5perc, windowWidth5perc },
            windowWidth5perc),
    };
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

[[nodiscard]] float TouchController::getHorizontalVelocity() const
{
    return model.leftJoystick.readJoystick().x;
}

[[nodiscard]] bool TouchController::isJumpPressed() const
{
    return model.jumpButton.readButton();
}

[[nodiscard]] bool TouchController::isBackPressed() const
{
    return model.pauseButton.readButton();
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
    if (!model.fingerToTouchObject.contains(e.finger)) return;

    auto idx = model.fingerToTouchObject.at(e.finger);
    model.fingerToTouchObject.erase(e.finger);
    model.objects[idx].reset();
}

void TouchController::processEvent(const sf::Event::TouchMoved& e)
{
    // Update touchPosition, but normalize it so it stays inside the touchArea
    // even when the finger moves out of it
    if (!model.fingerToTouchObject.contains(e.finger)) return;

    auto idx = model.fingerToTouchObject.at(e.finger);
    auto& obj = model.objects[idx];
    auto direction = sf::Vector2f(e.position) - obj.touchArea.getPosition();
    auto length = direction.length();
    obj.touchPosition =
        obj.touchArea.getPosition()
        + dgm::Math::toUnit(direction)
              * std::clamp(length, 0.f, obj.touchArea.getRadius());
}
