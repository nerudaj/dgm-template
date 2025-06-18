#include "appstate/AppStateGame.hpp"
#include "appstate/AppStatePause.hpp"
#include "appstate/Messaging.hpp"

void AppStateGame::input()
{
    if (dic.input.isBackButtonPressed())
    {
        app.pushState<AppStatePause>(dic, settings);
    }

    while (const auto event = app.window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            app.exit();
        }
    }
}

void AppStateGame::update()
{
    gameRulesEngine.update(app.time);
    renderingEngine.update(app.time);

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

    auto world = box::createWorld();
    auto&& ground =
        box::createStaticBox(world, b2Vec2(20.f, 22.f), b2Vec2(40.f, 1.f));
    auto&& playerBody = box::createDynamicBall(
        world,
        b2Vec2(20.f, 10.f),
        1.f,
        DynamicBodyProperties {
            .restitution = 0.f,
        });

    return Scene {
        .dummy =
            DummyEntity {
                .body = playerBody,
                .animation = std::move(animation),
            },
        .world = std::move(world),
        .ground = ground,
    };
}
