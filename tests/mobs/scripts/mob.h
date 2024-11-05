#pragma once

#include <box2d/box2d.h>
#include <core.h>

class Mob : public entix::ecs::component::Script {
    b2BodyId bodyId = b2_nullBodyId;

   public:
    void onAttach() override {
        auto bodyDef = b2DefaultBodyDef();
        bodyDef.type = b2_dynamicBody;
        bodyDef.position = (b2Vec2){PXtoM(400), PXtoM(100)};

        if (auto world = entix::ResourceManager::Get()
                             ->read<entix::resource::PhysicWorld>();
            world) {
            bodyId = b2CreateBody(world->worldId, &bodyDef);

            auto square = b2MakeSquare(PXtoM(16));
            auto shapeDef = b2DefaultShapeDef();
            shapeDef.restitution = 0.2f;

            b2CreatePolygonShape(bodyId, &shapeDef, &square);
        }
    }

    void setPosition(const b2Vec2& position) {
        if (b2Body_IsValid(bodyId))
            b2Body_SetTransform(bodyId, position, b2Rot_identity);
    }

    void Update(uint32_t) override {
        if (!b2Body_IsValid(bodyId)) return;

        auto position = b2Body_GetPosition(bodyId);
        auto rotation = b2Rot_GetAngle(b2Body_GetRotation(bodyId));

        auto& transform = get<entix::ecs::component::Transform>();
        transform.position.x = MtoPX(position.x);
        transform.position.y = MtoPX(position.y);
        transform.rotation = rotation * 180 / b2_pi;
    }
};