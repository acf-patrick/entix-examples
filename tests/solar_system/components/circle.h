#pragma once

#include <SDL2_gfxPrimitives.h>
#include <core.h>

class Circle : public entix::ecs::Script {
    int _radius;
    SDL_Color _color;

   public:
    Circle(int radius, const SDL_Color& color)
        : _radius(radius), _color(color) {}

    void Render() override {
        if (!has<entix::ecs::component::Transform>()) return;

        entix::core::RenderManager::Get()->submit([&](SDL_Renderer* renderer) {
            const auto& position =
                get<entix::ecs::component::Transform>().position;

            filledCircleRGBA(renderer, (Sint16)position.x, (Sint16)position.y,
                             (Sint16)_radius, _color.r, _color.g, _color.b,
                             _color.a);
        });
    }
};