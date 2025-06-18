#pragma once

#include "misc/CoordConverter.hpp"
#include <DGM/classes/Time.hpp>
#include <box2d/box2d.h>

using PhysicsWorld = std::unique_ptr<b2World>;
using PhysicsBody = b2Body&;
using PhysicsCollider = b2Fixture;

struct DynamicBodyProperties
{
    float density = 1.0f;
    float friction = 0.5f;
    float restitution = 0.2f; // Bounciness
};

namespace box
{
    const static inline b2Vec2 GRAVITY = b2Vec2(0.0f, 9.8f);

    static PhysicsWorld createWorld()
    {
        return std::make_unique<b2World>(GRAVITY);
    }

    static PhysicsBody createBody(
        PhysicsWorld& world, b2Vec2 position, b2BodyType type = b2_staticBody)
    {
        b2BodyDef bodyDef;
        bodyDef.position.Set(position.x, position.y);
        bodyDef.type = type;
        return *world->CreateBody(&bodyDef);
    }

    static PhysicsBody
    createStaticBox(PhysicsWorld& world, b2Vec2 position, b2Vec2 size)
    {
        auto&& body = createBody(world, position);
        b2PolygonShape boxShape;
        boxShape.SetAsBox(size.x / 2.0f, size.y / 2.0f);
        body.CreateFixture(&boxShape, 0.0f);
        return body;
    }

    static PhysicsBody createDynamicBall(
        PhysicsWorld& world,
        b2Vec2 position,
        float radius,
        const DynamicBodyProperties& properties = {})
    {
        auto&& body = createBody(world, position, b2_dynamicBody);

        b2CircleShape circleShape;
        circleShape.m_radius = radius;

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &circleShape;
        fixtureDef.density = properties.density;
        fixtureDef.friction = properties.friction;
        fixtureDef.restitution = properties.restitution;

        body.CreateFixture(&fixtureDef);
        return body;
    }
} // namespace box

namespace box
{
    static inline void updateWorld(PhysicsWorld& world, const dgm::Time& time)
    {
        world->Step(time.getDeltaTime(), 6, 2);
    }
} // namespace box
