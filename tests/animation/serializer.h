#pragma once

#include <core.h>

#include "animations/animations.h"
#include "components/components.h"

class CustomSerializer : public entix::core::Serializer {
    void deserializeEntity(YAML::Node& node,
                           entix::ecs::Entity& entity) override {
        entix::core::Serializer::deserializeEntity(node, entity);

        if (auto squareNode = node["Square"]; squareNode)
            entity.attach<Square>(squareNode["Side"].as<int>());

        if (auto circleNode = node["Circle"]; circleNode)
            entity.attach<Circle>(circleNode["Radius"].as<int>());

        if (auto colorNode = node["Color"]; colorNode)
            entity.attach<SDL_Color>(colorNode.as<SDL_Color>());
    }

    std::shared_ptr<entix::task::ITask> deserializeTask(
        const YAML::Node& node, entix::ecs::Entity& entity) override {
        if (auto n = node["ColorChangeAnimation"]; n)
            return std::make_shared<ColorChangeAnimation>(
                entity, n["Duration"].as<int>(), n["From"].as<SDL_Color>(),
                n["To"].as<SDL_Color>());

        if (auto n = node["TranslationAnimation"]; n)
            return std::make_shared<TranslationAnimation>(
                entity, n["Duration"].as<int>(), n["To"].as<entix::VectorI>());

        return nullptr;
    }
};