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

        std::string fontPath("assets/fonts/Ubuntu-Regular.ttf");
        font = TTF_OpenFont(fontPath.c_str(), 24);

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
            auto fps = entix::core::Application::Get().getFramecount();
            auto fpsText = std::to_string(fps);
            fpsText += " FPS";

            auto surface =
                TTF_RenderText_Solid(font, fpsText.c_str(), {255, 255, 255});
            if (texture) {
                SDL_DestroyTexture(texture);
            }

            texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);

            destination.w = surface->w;
            destination.h = surface->h;

            if (texture) {
                SDL_RenderCopy(renderer, texture, NULL, &destination);
            }
        });
    }
};
