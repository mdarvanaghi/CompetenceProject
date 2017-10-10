#include "Systems/RenderSystem.h"
#include "Constants.h"

namespace Motherload
{
    SDL_Renderer* RenderSystem::renderer;

    void RenderSystem::initialize(SDL_Window* window)
    {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer == nullptr)
        {
            std::cerr << "Could not create SDL Renderer." << std::endl;
        }

        SDL_SetRenderDrawColor
        (
            renderer,
            Constants::clearColor.x,
            Constants::clearColor.y,
            Constants::clearColor.z,
            Constants::clearColor.w
        );
    }

    SDL_Texture* RenderSystem::loadTexture(const std::string &file)
    {
        SDL_Texture* texture = IMG_LoadTexture(renderer, file.c_str());
        if (texture == nullptr)
        {
            std::cerr << "Texture load error." << std::endl;
        }
        return texture;
    }

    void RenderSystem::renderTexture(SDL_Texture* texture, int x, int y, int w, int h)
    {
        SDL_Rect destination;
        destination.x = x;
        destination.y = y;
        destination.w = w;
        destination.h = h;
        SDL_RenderCopy(renderer, texture, NULL, &destination);
    }

    void RenderSystem::renderScene()
    {
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
}