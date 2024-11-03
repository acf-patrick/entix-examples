#pragma once

#include <box2d/box2d.h>
#include <core.h>

#include "../consts.h"
#include "../resources/world.h"

class Ground : public entix::ecs::component::Script {
    b2BodyId bodyId = b2_nullBodyId;

   public:
    void onAttach() override {
        auto bodyDef = b2DefaultBodyDef();
        bodyDef.position = (b2Vec2){400 / MtoPX, 400 / MtoPX};
        bodyDef.type = b2_staticBody;

        auto world = entix::ResourceManager::Get()->read<World>();
        bodyId = b2CreateBody(world->worldId, &bodyDef);

        auto rect = b2MakeBox(300 / MtoPX, 10 / MtoPX);
        auto shapeDef = b2DefaultShapeDef();

        b2CreatePolygonShape(bodyId, &shapeDef, &rect);
    }

    void Render() override {
        entix::core::RenderManager::Get()->submit([&](SDL_Renderer* renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
            SDL_Rect rect = {100, 390, 600, 20};
            SDL_RenderDrawRect(renderer, &rect);
        });
    }
};