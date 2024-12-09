#pragma once

#include <SDL2_gfxPrimitives.h>
#include <core.h>

class Circle : public entix::ecs::Script {
    int _radius;

   public:
    Circle(int radius) : _radius(radius) {}

    void Render() override {
        if (!has<entix::ecs::component::Transform>()) return;

        SDL_Color color = {.r = 0xff, .g = 0xff, .b = 0xff, .a = 0xff};
        if (has<SDL_Color>()) {
            color = get<SDL_Color>();
        }

        const auto& position = get<entix::ecs::component::Transform>().position;

        entix::core::RenderManager::Get()->submit(
            [position, color, this](SDL_Renderer* renderer) {
                filledCircleRGBA(renderer, int(position.x + _radius),
                                 int(position.y + _radius), _radius, color.r,
                                 color.g, color.b, color.a);
            });
    }
};