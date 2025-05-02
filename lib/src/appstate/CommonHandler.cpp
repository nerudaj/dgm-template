#include "appstate/CommonHandler.hpp"

static void emulateGuiClick(Gui& gui, const sf::Vector2i& mousePos)
{
    gui.handleEvent(sf::Event::MouseButtonPressed {
        .button = sf::Mouse::Button::Left,
        .position = mousePos,
    });

    gui.handleEvent(sf::Event::MouseButtonReleased {
        .button = sf::Mouse::Button::Left,
        .position = mousePos,
    });
}

void CommonHandler::handleInput(
    dgm::App& app, DependencyContainer& dic, const InputSettings& settings)
{
    const auto mousePosition =
        sf::Mouse::getPosition(app.window.getSfmlWindowContext());

    if (dic.input.isConfirmPressed())
    {
        emulateGuiClick(dic.gui, mousePosition);
    }

    while (const auto event = app.window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            app.exit();
        else
        {
            dic.gui.handleEvent(*event);
        }
    }

    auto delta = dic.input.getCursorDelta() * settings.cursorSpeed
                 * app.time.getDeltaTime();

    sf::Mouse::setPosition(
        mousePosition + sf::Vector2i(delta), app.window.getSfmlWindowContext());
}
