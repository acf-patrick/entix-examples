#pragma once

#include <core.h>

class ButtonBehavior : public entix::ecs::Script {
    bool _isDarkMode = false;

   public:
    ButtonBehavior(bool isDarkMode) : _isDarkMode(isDarkMode) {}

    void onAttach() override {
        auto& sprite = get<entix::ecs::component::Sprite>();
        sprite.frame = _isDarkMode ? 0 : 1;

        event.listen(
            entix::core::Input::Event::MOUSE_BUTTON_UP,
            [&](entix::ecs::Entity& entity) {
                auto& mouseEvent = entity.get<SDL_MouseButtonEvent>();
                const auto& sprite = get<entix::ecs::component::Sprite>();
                if (auto optBoundingBox = sprite.getBoundingBox(
                        get<entix::ecs::component::Transform>());
                    optBoundingBox) {
                    auto& bb = *optBoundingBox;
                    SDL_Point mouse = {.x = mouseEvent.x, .y = mouseEvent.y};

                    if (SDL_PointInRect(&mouse, &bb)) {
                        entix::core::SceneManager::Get()->activateOrLoad(
                            _isDarkMode ? "light" : "dark");
                    }
                }
            });
    }

    void Render() override {}

    void Update(uint32_t) override {}
};