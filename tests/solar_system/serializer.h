#pragma once

#include <core.h>

#include "components/components.h"

class Serializer : public entix::core::Serializer {
    void deserializeEntity(YAML::Node& node,
                           entix::ecs::Entity& entity) override {
        entix::core::Serializer::deserializeEntity(node, entity);

        auto n = node["Circle"];
        if (n) {
            entity.attach<Circle>(n["Radius"].as<int>(),
                                  n["Color"].as<SDL_Color>());
        }

        n = node["Planet"];
        if (n) {
            entity.attach<Planet>(n["TrajectoryRadius"].as<entix::VectorF>(),
                                  n["Speed"].as<float>());
        }

        n = node["EllipseSpawner"];
        if (n) entity.attach<EllipseSpawner>();
    }
};
