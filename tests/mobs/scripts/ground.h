#pragma once

#include <box2d/box2d.h>
#include <core.h>

class Ground : public entix::ecs::component::Script {
   public:
    void onAttach() override {
        auto bodyDef = b2DefaultBodyDef();
        bodyDef.position = (b2Vec2){PXtoM(400), PXtoM(400)};
        bodyDef.type = b2_staticBody;

        if (auto world = entix::ResourceManager::Get()
                             ->read<entix::resource::PhysicWorld>();
            world) {
            auto bodyId = b2CreateBody(world->worldId, &bodyDef);

            auto rect = b2MakeBox(PXtoM(300), PXtoM(10));
            auto shapeDef = b2DefaultShapeDef();

            b2CreatePolygonShape(bodyId, &shapeDef, &rect);
        }
    }

    void Render() override {
        entix::core::RenderManager::Get()->submit([&](SDL_Renderer* renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
            SDL_Rect rect = {100, 390, 600, 20};
            SDL_RenderDrawRect(renderer, &rect);
        });
    }
};