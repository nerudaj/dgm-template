#include "appstate/AppStateGame.hpp"
#include "appstate/AppStatePause.hpp"
#include "appstate/Messaging.hpp"

void AppStateGame::input()
{
    dic.input.update();

    if (dic.input.isBackButtonPressed())
    {
        app.pushState<AppStatePause>(dic, settings);
    }
}

void AppStateGame::update()
{
    gameRulesEngine.update(app.time.getDeltaTime());
}

void AppStateGame::draw()
{
    renderingEngine.draw(app.window);
}

void AppStateGame::restoreFocusImpl(const std::string& msg)
{
    if (auto message = Messaging::deserialize(msg))
    {
        std::visit([&](PopIfNotMenu&) { app.popState(msg); }, *message);
    }
}
