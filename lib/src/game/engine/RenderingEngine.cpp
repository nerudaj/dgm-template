#include "game/engine/RenderingEngine.hpp"

void RenderingEngine::update(const dgm::Time& time)
{
    fpsCounter.update(time.getDeltaTime());
    ground.setPosition(
        CoordConverter::worldToScreen(scene.ground.GetPosition()));
    playerCollider.setPosition(
        CoordConverter::worldToScreen(scene.dummy.body.GetPosition()));
    playerSprite.setPosition(playerCollider.getPosition());
}

void RenderingEngine::draw(dgm::Window& window)
{
    window.draw(ground);

    playerSprite.setTextureRect(scene.dummy.animation.getCurrentFrame());
    playerSprite.setScale({ scene.dummy.facingLeft ? -1.f : 1.f, 1.f });

    window.draw(playerSprite);
    window.draw(playerCollider);

    text.setString(fpsCounter.getText());
    window.draw(text);
}