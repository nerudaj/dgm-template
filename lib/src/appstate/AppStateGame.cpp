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
    gameRulesEngine.update(app.time);

    gameEvents.processEvents(
        [&](const DummyGameEvent& e)
        {
            sound.setBuffer(dic.resmgr.get<sf::SoundBuffer>(e.soundName));
            sound.play();
        });
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

Scene AppStateGame::buildScene(const dgm::ResourceManager& resmgr)
{
    auto&& animation =
        dgm::Animation(resmgr.get<dgm::AnimationStates>("mrman.png.anim"), 4);
    animation.setState("idle", true);

    return Scene {
        .dummy =
            DummyEntity {
                .body = dgm::Rect({ 100.f, 100.f }, { 32.f, 60.f }),
                .animation = std::move(animation),
            },
    };
}
