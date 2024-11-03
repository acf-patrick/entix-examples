#pragma once

#include <box2d/box2d.h>
#include <core.h>

#include "../consts.h"
#include "../resources/world.h"

class Mob : public entix::ecs::component::Script {
   public:
    b2BodyId bodyId = b2_nullBodyId;
    Uint32 lastTick;

    void onAttach() override {
        auto bodyDef = b2DefaultBodyDef();
        bodyDef.type = b2_dynamicBody;
        bodyDef.position = (b2Vec2){400 / MtoPX, 100 / MtoPX};

        auto world = entix::ResourceManager::Get()->read<World>();
        bodyId = b2CreateBody(world->worldId, &bodyDef);

        auto square = b2MakeSquare(16 / MtoPX);
        auto shapeDef = b2DefaultShapeDef();
        shapeDef.restitution = 0.2f;

        b2CreatePolygonShape(bodyId, &shapeDef, &square);
    }

    void Update(uint32_t) override {
        auto position = b2Body_GetPosition(bodyId);
        auto rotation = b2Rot_GetAngle(b2Body_GetRotation(bodyId));

        auto& transform = get<entix::ecs::component::Transform>();
        transform.position.x = position.x * MtoPX;
        transform.position.y = position.y * MtoPX;
        transform.rotation = rotation * 180 / b2_pi;
    }
};