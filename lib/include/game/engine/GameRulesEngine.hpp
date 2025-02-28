#pragma once

#include "game/events/GameEvents.hpp"
#include "game/Scene.hpp"
#include "game/events/EventQueue.hpp"

class [[nodiscard]] GameRulesEngine final
{
public:
    GameRulesEngine(
        EventQueue<GameEvent>& gameEventQueue,
        Scene& scene) noexcept
    : gameEventQueue(gameEventQueue)
    , scene(scene) {}
    GameRulesEngine(GameRulesEngine&&) = delete;
    GameRulesEngine(const GameRulesEngine&) = delete;

public:
    void operator()(const DummyGameEvent& e);

    void update(const float deltaTime);

private:
    EventQueue<GameEvent>& gameEventQueue;
    Scene& scene;
};