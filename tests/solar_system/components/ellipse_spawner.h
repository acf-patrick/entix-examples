#pragma once

#include <SDL2_gfxPrimitives.h>
#include <core.h>

class EllipseSpawner : public entix::ecs::Script {
    class Ellipse : public entix::ecs::Script {
        entix::VectorF _radius;
        SDL_Color _color;

       public:
        Ellipse(const entix::VectorF& radius, const SDL_Color& color)
            : _radius(radius), _color(color) {}

        void Render() override {
            entix::core::RenderManager::Get()->submit(
                [&](SDL_Renderer* renderer) {
                    const auto center =
                        entix::core::RenderManager::Get()->getSize() * 0.5;
                    aaellipseRGBA(renderer, (Sint16)(center.x),
                                  (Sint16)(center.y), (Sint16)_radius.x,
                                  (Sint16)_radius.y, _color.r, _color.g,
                                  _color.b, _color.a);
                });
        }
    };

   public:
    EllipseSpawner() = default;

    void onAttach() override {
        auto group = get<entix::ecs::component::Group>().group;

        const SDL_Color ellipseColor = {.r = 155, .g = 255, .b = 155, .a = 255};
        const entix::VectorI radius(125, 65), radiusPace(35, 25);

        for (int i = 0; i < 8; ++i) {
            group->create().attach<Ellipse>(radius + radiusPace * i,
                                            ellipseColor);
        }
    }
};