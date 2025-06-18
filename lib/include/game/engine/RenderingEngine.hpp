#pragma once

#include "game/Scene.hpp"
#include "misc/FpsCounter.hpp"
#include <DGM/dgm.hpp>

class [[nodiscard]] RenderingEngine final
{
public:
    RenderingEngine(dgm::ResourceManager& resmgr, Scene& scene) noexcept
        : scene(scene)
        , text(resmgr.get<sf::Font>("ChunkFive-Regular.ttf"))
        , ground(CoordConverter::worldToScreen(b2Vec2(40.f, 1.f)))
        , playerCollider(CoordConverter::worldToScreen(1.f))
        , playerSprite(resmgr.get<sf::Texture>("mrman.png"))
    {
        ground.setOrigin(ground.getSize() / 2.f);
        ground.setFillColor(sf::Color(128, 192, 0));
        playerCollider.setFillColor(sf::Color(255, 255, 0, 128));
        playerSprite.setOrigin(
            sf::Vector2f(scene.dummy.animation.getCurrentFrame().size) / 2.f);
    }

    RenderingEngine(RenderingEngine&&) = delete;
    RenderingEngine(const RenderingEngine&) = delete;

public:
    void update(const dgm::Time& time);

    void draw(dgm::Window& window);

private:
    Scene& scene;
    FpsCounter fpsCounter;
    sf::Text text;

    // Dummy objects
    sf::RectangleShape ground;
    sf::CircleShape playerCollider;
    sf::Sprite playerSprite;
};
