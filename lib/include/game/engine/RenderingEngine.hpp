#pragma once

#include "game/Scene.hpp"
#include "misc/FpsCounter.hpp"
#include <DGM/dgm.hpp>

class [[nodiscard]] RenderingEngine final
{
public:
    RenderingEngine(
        dgm::ResourceManager& resmgr,
        Scene& scene,
        const sf::Vector2f& resolution) noexcept
        : scene(scene)
        , worldCamera(
              createFullscreenCamera(resolution, INTERNAL_GAME_RESOLUTION))
        , hudCamera(sf::FloatRect { { 0.f, 0.f }, { 1.f, 1.f } }, resolution)
        , text(resmgr.get<sf::Font>("ChunkFive-Regular.ttf"))
        , sprite(resmgr.get<sf::Texture>("mrman.png"))
    {
        sprite.setOrigin(
            sf::Vector2f(scene.dummy.animation.getCurrentFrame().size) / 2.f);
        ground.setPosition(scene.groundPosition);
        ground.setFillColor(sf::Color(128, 192, 0));
        ground.setSize({ INTERNAL_GAME_RESOLUTION.x,
                         INTERNAL_GAME_RESOLUTION.y - scene.groundPosition.y });
    }

    RenderingEngine(RenderingEngine&&) = delete;
    RenderingEngine(const RenderingEngine&) = delete;

public:
    void update(const dgm::Time& time);

    void draw(dgm::Window& window);

private:
    /**
     * \brief Create fullscreen camera with a fixed resolution and aspect ratio
     *
     * When porting games to multiple systems / resolutions / aspect ratio, the
     * renderer can show less / more than you need to. This function allows you
     * to run the game at some fixed internal resolution, inserting black bars
     * if the aspect ratio of the current device mismatches your desired aspect
     * ratio.
     */
    static dgm::Camera createFullscreenCamera(
        const sf::Vector2f& currentResolution,
        const sf::Vector2f& desiredResolution);

private:
    const static inline auto INTERNAL_GAME_RESOLUTION =
        sf::Vector2f { 1280.f, 720.f };

    Scene& scene;
    dgm::Camera worldCamera;
    dgm::Camera hudCamera;

    FpsCounter fpsCounter;
    sf::Text text;

    sf::Sprite sprite;
    sf::RectangleShape ground;
};
