#pragma once

#include <core.h>

#include "../components/square.h"

class ColorChangeAnimation : public entix::task::ITask {
    entix::ecs::Entity& _entity;

    bool _firstRun = true;
    entix::util::LazyTimer _timer;
    SDL_Color _startColor, _finalColor;

   public:
    ColorChangeAnimation(entix::ecs::Entity& entity, Uint32 animationDuration,
                         const SDL_Color& from, const SDL_Color& to)
        : _entity(entity),
          _timer(animationDuration),
          _startColor(from),
          _finalColor(to) {}

    bool done() const override { return _timer.isDone(); }

    void run(uint32_t) override {
        auto& square = _entity.get<Square>();

        if (_firstRun) {
            _firstRun = false;
            _timer.resume();
        }

        auto color =
            entix::util::lerp(_startColor, _finalColor, _timer.getProgress());
        square.setColor(color);
    }
};
