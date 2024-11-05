#pragma once

#include "scripts/scripts.h"
#include "serializer/serializer.h"

class CustomSerializer : public entix::core::Serializer {
   public:
    void deserializeEntity(YAML::Node& node,
                           entix::ecs::Entity& entity) override {
        Serializer::deserializeEntity(node, entity);

        auto c = node["Mob"];
        if (c) entity.attach<Mob>();

        c = node["Ground"];
        if (c) entity.attach<Ground>();

        c = node["FollowMouseBehavior"];
        if (c) entity.attach<FollowMouseBehavior>();

        c = node["FpsText"];
        if (c) entity.attach<FpsText>();
    }
};