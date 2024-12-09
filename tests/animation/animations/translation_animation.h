#pragma once

#include <core.h>

#include "../components/components.h"

class TranslationAnimation : public entix::task::ITask {
    entix::util::LazyTimer _timer;
    entix::VectorD _initialPosition, _destination;
    entix::ecs::Entity& _entity;
    bool _firstRun = true;

   public:
    TranslationAnimation(entix::ecs::Entity& entity, Uint32 duration,
                         const entix::VectorI& to)
        : _entity(entity), _timer(duration), _destination(to.x, to.y) {}

    bool done() const override { return _timer.isDone(); }

    void run(uint32_t) override {
        if (!_entity.has<SDL_Color>()) return;

        auto& position =
            _entity.get<entix::ecs::component::Transform>().position;

        if (_firstRun) {
            _timer.resume();
            _initialPosition = position;
            _firstRun = false;
        }

        position = entix::util::lerp(_initialPosition, _destination,
                                     _timer.getProgress());
    }
};