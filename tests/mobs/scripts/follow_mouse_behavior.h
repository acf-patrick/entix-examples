#pragma once

#include <core.h>

class FollowMouseBehavior : public entix::ecs::component::Script {
   public:
    FollowMouseBehavior() {
        event.listen(entix::core::Input::Event::MOUSE_MOTION,
                     [&](entix::ecs::Entity& entity) {
                         auto& position =
                             get<entix::ecs::component::Transform>().position;
                         auto event = entity.get<SDL_MouseMotionEvent>();
                         position.set(event.x, event.y);
                     });
    }
};