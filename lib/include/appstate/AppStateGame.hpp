#pragma once

#include "game/definitions/GameScene.hpp"
#include "game/engine/GameRulesEngine.hpp"
#include "game/engine/RenderingEngine.hpp"
#include "misc/DependencyContainer.hpp"
#include "misc/EventQueue.hpp"
#include "settings/AppSettings.hpp"
#include <DGM/dgm.hpp>
#include <SFML/Audio.hpp>
#include <vector>

class [[nodiscard]] AppStateGame : public dgm::AppState
{
public:
    AppStateGame(dgm::App& app, DependencyContainer& dic)
        : dgm::AppState(app)
        , dic(dic)
        , scene(buildScene(dic.resmgr))
        , gameRulesEngine(gameEvents, scene, dic.input)
        , renderingEngine(dic.resmgr, scene, dic.settings, dic.touchController)
    {
    }

public:
    void input() override;

    void update() override;

    void draw() override;

private:
    void restoreFocusImpl(const std::string& msg) override;

    static GameScene buildScene(const dgm::ResourceManager& resmgr);

private:
    DependencyContainer& dic;
    GameScene scene;
    EventQueue<GameEvent> gameEvents;
    GameRulesEngine gameRulesEngine;
    RenderingEngine renderingEngine;
};
