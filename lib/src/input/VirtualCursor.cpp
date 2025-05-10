#include "input/VirtualCursor.hpp"

void VirtualCursor::update(const dgm::Time& time)
{
    const auto delta = input.getCursorDelta();
    if (delta == sf::Vector2f(0.f, 0.f))
    {
        position = sf::Vector2f(sf::Mouse::getPosition(window));
        return;
    };

    position += delta * time.getDeltaTime();

    clampPosition(window.getSize());
    sf::Mouse::setPosition(sf::Vector2i(position), window);
}

void VirtualCursor::emulateClick(Gui& gui)
{
    gui.handleEvent(sf::Event::MouseButtonPressed {
        .button = sf::Mouse::Button::Left,
        .position = sf::Vector2i(position),
    });
    gui.handleEvent(sf::Event::MouseButtonReleased {
        .button = sf::Mouse::Button::Left,
        .position = sf::Vector2i(position),
    });
}

void VirtualCursor::draw(dgm::Window& window)
{
    sprite.setPosition(position);
    window.draw(sprite);
}

void VirtualCursor::clampPosition(const sf::Vector2u& windowSize)
{
    position.x = std::clamp(position.x, 0.f, static_cast<float>(windowSize.x));
    position.y = std::clamp(position.y, 0.f, static_cast<float>(windowSize.y));
}
