#pragma once

#include "gui/Gui.hpp"
#include "input/Input.hpp"
#include <DGM/dgm.hpp>

/**
 *  \brief Class that represents menu cursor that can be
 *  moved on screen by means of gamepad and other sources.
 */
class [[nodiscard]] VirtualCursor final
{
public:
    VirtualCursor(
        const sf::RenderWindow& window,
        Input& input,
        const sf::Texture& cursorTexture)
        : window(window), input(input), sprite(cursorTexture)
    {
    }

public:
    void update(const dgm::Time& time);

    void emulateClick(Gui& gui);

    void draw(dgm::Window& window);

private:
    void clampPosition(const sf::Vector2u& windowSize);

private:
    const sf::RenderWindow& window;
    Input& input;
    sf::Sprite sprite;
    sf::Vector2f position;
};