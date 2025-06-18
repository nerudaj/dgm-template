#pragma once

#include "misc/Box2D.hpp"
#include <DGM/dgm.hpp>

// You can delete this one
struct DummyEntity
{
    PhysicsBody body;
    dgm::Animation animation;
    bool facingLeft = false;
    sf::Vector2f forward = { 0.f, 0.f };
};

struct [[nodiscard]] Scene final
{
    DummyEntity dummy;
    PhysicsWorld world;
    PhysicsBody ground;
};
