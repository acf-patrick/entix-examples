#pragma once

#include <ecs/ecs.h>
#include <scene/scene.h>

class MoveFirstCamera : public entix::ecs::Script {
   public:
    void Update(uint32_t dt) override {
        using Input = entix::core::Input;
        const float speed = 2;
        auto& camera = entix::core::SceneManager::Get()
                           ->getActive()
                           .getEntity("main camera")
                           ->get<entix::ecs::component::Transform>()
                           .position;

        if (Input::isKeyPressed(SDL_SCANCODE_UP)) camera.y += speed;

        if (Input::isKeyPressed(SDL_SCANCODE_DOWN)) camera.y -= speed;

        if (Input::isKeyPressed(SDL_SCANCODE_RIGHT)) camera.x -= speed;

        if (Input::isKeyPressed(SDL_SCANCODE_LEFT)) camera.x += speed;
    }
};

class MoveSecondCamera : public entix::ecs::Script {
   public:
    void Update(uint32_t dt) override {
        using Input = entix::core::Input;
        const float speed = 2;
        auto& camera = entix::core::SceneManager::Get()
                           ->getActive()
                           .getEntity("secondary camera")
                           ->get<entix::ecs::component::Transform>()
                           .position;

        if (Input::isKeyPressed(SDL_SCANCODE_KP_8)) camera.y += speed;

        if (Input::isKeyPressed(SDL_SCANCODE_KP_5)) camera.y -= speed;

        if (Input::isKeyPressed(SDL_SCANCODE_KP_6)) camera.x -= speed;

        if (Input::isKeyPressed(SDL_SCANCODE_KP_4)) camera.x += speed;
    }
};