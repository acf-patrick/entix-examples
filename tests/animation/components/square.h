#pragma once

#include <SDL2_gfxPrimitives.h>
#include <core.h>

class Square : public entix::ecs::Script {
    int _side = 16;

   public:
    Square(int side) : _side(side) {}

    void Render() override {
        if (!has<entix::ecs::component::Transform>()) return;

        SDL_Color color = {.r = 0xff, .g = 0xff, .b = 0xff, .a = 0xff};
        if (has<SDL_Color>()) {
            color = get<SDL_Color>();
        }

        const auto& position = get<entix::ecs::component::Transform>().position;

        entix::core::RenderManager::Get()->submit(
            [position, color, this](SDL_Renderer* renderer) {
                SDL_Rect rect = {.x = (int)position.x,
                                 .y = (int)position.y,
                                 .w = _side,
                                 .h = _side};
                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b,
                                       color.a);
                SDL_RenderFillRect(renderer, &rect);
            });
    }
};