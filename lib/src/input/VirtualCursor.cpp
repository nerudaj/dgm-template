#include "input/VirtualCursor.hpp"

void VirtualCursor::update(const dgm::Time& time, const float cursorSpeed)
{
    const auto delta = input.getCursorDelta();
    if (delta == sf::Vector2f(0.f, 0.f))
    {
        position = sf::Vector2f(sf::Mouse::getPosition(window));
        return;
    };

    position = clampPositionByWindow(
        position + delta * cursorSpeed * time.getDeltaTime(), window.getSize());
    sf::Mouse::setPosition(sf::Vector2i(position), window);
}

void VirtualCursor::draw()
{
    sprite.setPosition(position);
    window.draw(sprite);
}

sf::Vector2f VirtualCursor::clampPositionByWindow(
    const sf::Vector2f& currentPosition, const sf::Vector2u& windowSize)
{
    return sf::Vector2f {
        std::clamp(currentPosition.x, 0.f, static_cast<float>(windowSize.x)),
        std::clamp(currentPosition.y, 0.f, static_cast<float>(windowSize.y))
    };
}
