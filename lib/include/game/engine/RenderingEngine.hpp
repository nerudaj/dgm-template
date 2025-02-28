#pragma once

#include "game/Scene.hpp"
#include <DGM/dgm.hpp>

class [[nodiscard]] RenderingEngine final
{
public:
    RenderingEngine(Scene& scene) noexcept : scene(scene) {}
    RenderingEngine(RenderingEngine&&) = delete;
    RenderingEngine(const RenderingEngine&) = delete;

public:
    void draw(dgm::Window& window);

private:
    Scene& scene;
};
