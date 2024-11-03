#pragma once

#include <box2d/box2d.h>

struct World {
    b2WorldId worldId = b2_nullWorldId;
    b2Vec2 gravity;

    World(const b2Vec2& gravity) : gravity(gravity) {
        auto worldDef = b2DefaultWorldDef();
        worldDef.gravity = gravity;
        worldId = b2CreateWorld(&worldDef);
    }
};