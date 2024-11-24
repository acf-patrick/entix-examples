#pragma once

#include <SDL2_gfxPrimitives.h>
#include <core.h>

class Square : public entix::ecs::Script {
    enum class Position { TopLeft, BottomLeft, BottomRight, TopRight, Unused };

    SDL_Color _color;
    int _side = 16;
    int _index;
    Position _position = Position::Unused;

    Position nextPosition() const {
        if (_position == Position::Unused) return _position;

        if (_position == Position::TopRight) return Position::TopLeft;
        return (Position)(int(_position) + 1);
    }

   public:
    Square(int index, int side, const SDL_Color& color)
        : _color(color), _side(side), _index(index) {
        if (index == 0) _position = Position::TopRight;
    }

    void setColor(const SDL_Color& color) { _color = color; }

    SDL_Color getColor() const { return _color; }

    void Render() override {
        if (!has<entix::ecs::component::Transform>()) return;

        const auto& position = get<entix::ecs::component::Transform>().position;

        entix::core::RenderManager::Get()->submit(
            [position, this](SDL_Renderer* renderer) {
                SDL_Rect rect = {.x = (int)position.x,
                                 .y = (int)position.y,
                                 .w = _side,
                                 .h = _side};
                SDL_SetRenderDrawColor(renderer, _color.r, _color.g, _color.b,
                                       _color.a);
                SDL_RenderFillRect(renderer, &rect);
            });
    }
};