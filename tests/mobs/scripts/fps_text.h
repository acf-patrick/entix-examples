#pragma once

#include <SDL_ttf.h>
#include <core.h>

class FpsText : public entix::ecs::component::Script {
    TTF_Font* font;

    SDL_Rect destination;
    SDL_Texture* texture = nullptr;

   public:
    FpsText() {
        destination.x = destination.y = 10;

        auto fontPath(entix::core::Application::Get().getConfigPath() /
                      "fonts/emulogic.ttf");
        font = TTF_OpenFont(fontPath.string().c_str(), 16);

        if (!font) {
            entix::Logger::error("FpsText") << "Unable to load " << fontPath;
            entix::Logger::endline();
        }
    }

    ~FpsText() {
        TTF_CloseFont(font);
        SDL_DestroyTexture(texture);
    }

    void Render() override {
        entix::core::RenderManager::Get()->submit([&](SDL_Renderer* renderer) {
            auto fps = entix::core::Application::Get().getFramerate();
            auto fpsText = "FPS : " + std::to_string(fps);

            if (auto surface = TTF_RenderText_Solid(font, fpsText.c_str(),
                                                    {255, 255, 255});
                surface) {
                if (texture) {
                    SDL_DestroyTexture(texture);
                }

                texture = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_FreeSurface(surface);

                destination.w = surface->w;
                destination.h = surface->h;
            }

            if (texture) {
                SDL_RenderCopy(renderer, texture, NULL, &destination);
            }
        });
    }
};
