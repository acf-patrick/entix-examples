#pragma once

#include <core.h>

class SpriteAnimator : public entix::ecs::component::Script {
    // frame duration in milliseconds
    Uint32 frameDuration;

    Uint32 latestTick;

   public:
    SpriteAnimator(Uint32 frameDuration) : frameDuration(frameDuration) {
        latestTick = SDL_GetTicks();
    }

    void Update(uint32_t) override {
        auto currentTick = SDL_GetTicks();
        if (currentTick - latestTick >= frameDuration) {
            latestTick = currentTick;

            auto& sprite = get<entix::ecs::component::Sprite>();
            sprite.frame++;
            sprite.frame %= sprite.framesNumber.x;

            // skip first frame
            if (sprite.frame == 0) {
                sprite.frame = 1;
            }
        }
    }
};