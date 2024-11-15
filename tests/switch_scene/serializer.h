#pragma once

#include <core.h>

#include "./scripts/scripts.h"

class CustomSerializer : public entix::core::Serializer {
   public:
    void deserializeEntity(YAML::Node& node,
                           entix::ecs::Entity& entity) override {
        entix::core::Serializer::deserializeEntity(node, entity);
        if (auto buttonNode = node["ButtonBehavior"]; buttonNode)
            entity.attach<ButtonBehavior>(buttonNode["DarkMode"].as<bool>());
    }
};