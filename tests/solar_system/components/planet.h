#pragma once

#include <core.h>

#include <cmath>

class Planet : public entix::ecs::Script {
    entix::VectorF _trajectoryRadius;
    float _theta = 0.0;
    float _speed;

   public:
    Planet(const entix::VectorF& trajectoryRadius, float speed)
        : _trajectoryRadius(trajectoryRadius), _speed(speed) {}

    void Update(uint32_t dt) override {
        if (!has<entix::ecs::component::Transform>()) {
            attach<entix::ecs::component::Transform>();
        }

        auto& position = get<entix::ecs::component::Transform>().position;
        const auto screenCenter =
            entix::core::RenderManager::Get()->getSize() / 2.0;

        {
            const auto sin_theta = std::sin(_theta);
            const auto cos_theta = std::cos(_theta);
            const auto dtheta_dt =
                _speed / std::sqrt(_trajectoryRadius.x * _trajectoryRadius.x *
                                       sin_theta * sin_theta +
                                   _trajectoryRadius.y * _trajectoryRadius.y *
                                       cos_theta * cos_theta);

            _theta += dtheta_dt * (dt / 1000.0);
            if (_theta >= 2 * M_PI) _theta -= 2 * M_PI;
        }

        position.set(_trajectoryRadius.x * std::cos(_theta),
                     _trajectoryRadius.y * std::sin(_theta));
        position += screenCenter;
    }
};