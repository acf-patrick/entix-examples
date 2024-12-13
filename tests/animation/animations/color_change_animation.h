#pragma once

#include <core.h>

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
        if (!_entity.has<SDL_Color>()) return;

        auto& color = _entity.get<SDL_Color>();

        if (_firstRun) {
            _firstRun = false;
            _timer.resume();
        }

        color =
            entix::util::lerp(_startColor, _finalColor, _timer.getProgress());
    }
};
