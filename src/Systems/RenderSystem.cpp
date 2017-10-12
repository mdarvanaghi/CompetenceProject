#include "Systems/RenderSystem.h"
#include "Constants.h"
#include "Game.h"

namespace Motherload
{
    SDL_Renderer* RenderSystem::renderer;

    void RenderSystem::initialize(SDL_Window* window)
    {
        textureRect = new SDL_Rect();
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
            std::cerr << "Texture load error!" << std::endl;
        }
        return texture;
    }

    void RenderSystem::renderTexture(SDL_Texture* texture, glm::vec2 position, glm::vec2 scale)
    {
        textureRect->x = position.x;
        textureRect->y = position.y;
        textureRect->w = scale.x;
        textureRect->h = scale.y;
        SDL_RenderCopy(renderer, texture, NULL, textureRect);
    }

    void RenderSystem::renderScene()
    {
        SDL_RenderClear(renderer);
        drawEntities();
        SDL_RenderPresent(renderer);
    }

    void RenderSystem::drawEntities()
    {
        for (auto& vector : Game::instance->blocks)
        {
            for (auto& block : vector)
            {
                if (block->texture == nullptr)
                {
                    std::cerr << "Texture is nullptr" << std::endl;
                }
                renderTexture(block->texture, block->transform->getPositionCameraSpace(), block->transform->getScaleCameraSpace());
            }
        }
    }
}