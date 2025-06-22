#include "game/engine/RenderingEngine.hpp"

void RenderingEngine::update(const dgm::Time& time)
{
    fpsCounter.update(time.getDeltaTime());
}

void RenderingEngine::draw(dgm::Window& window)
{
    // Render the game world
    window.setViewFromCamera(worldCamera);

    sprite.setTextureRect(scene.dummy.animation.getCurrentFrame());
    sprite.setPosition(scene.dummy.body.getCenter());
    sprite.setScale({ scene.dummy.facingLeft ? -1.f : 1.f, 1.f });

    scene.dummy.body.debugRender(window); // rendering hitbox
    window.draw(ground);
    window.draw(sprite);

    // Render everything hud-related
    window.setViewFromCamera(hudCamera);

    text.setString(fpsCounter.getText());
    window.draw(text);
}

dgm::Camera RenderingEngine::createFullscreenCamera(
    const sf::Vector2f& currentResolution,
    const sf::Vector2f& desiredResolution)
{
    auto&& viewport = sf::FloatRect {
        { 0.f, 0.f },
        { 1.f, 1.f },
    };

    const auto&& desiredAspectRatio = desiredResolution.x / desiredResolution.y;
    const auto&& currentAspectRatio = currentResolution.x / currentResolution.y;

    if (currentAspectRatio > desiredAspectRatio)
    {
        // Narrow desired into wider current
        viewport.size.x = desiredResolution.y / currentResolution.y;
        viewport.position.x = (1.f - viewport.size.x) / 2.f;
    }
    else if (currentAspectRatio < desiredAspectRatio)
    {
        // Wider desired into narrower current
        viewport.size.y = desiredResolution.x / currentResolution.x;
        viewport.position.y = (1.f - viewport.size.y) / 2.f;
    }

    return dgm::Camera(viewport, sf::Vector2f(desiredResolution));
}
