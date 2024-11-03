#pragma once

#include <box2d/box2d.h>

#include "consts.h"
#include "ecs/system/system.h"
#include "resources/world.h"

class WorldSystem : public entix::ecs::ISystem {
    entix::core::EventListner eventListner;
    b2WorldId worldId = b2_nullWorldId;

   public:
    WorldSystem() : ISystem("WorldSystem") {}

    ~WorldSystem() {
        b2DestroyWorld(worldId);
    }

    bool run() override {
        if (!b2World_IsValid(worldId)) {
            worldId = entix::ResourceManager::Get()->read<World>()->worldId;
        }

        b2World_Step(worldId, timeStep, 6);
        return true;
    }
};