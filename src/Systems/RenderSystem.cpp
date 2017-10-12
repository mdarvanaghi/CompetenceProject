#include "Systems/RenderSystem.h"

namespace Motherload
{
    SDL_Renderer* RenderSystem::renderer;
    SDL_Rect* RenderSystem::textureRect;
    bool RenderSystem::debugDraw;
    bool RenderSystem::textureDraw;

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
        /* Clear renderer */
        SDL_SetRenderDrawColor
        (
            renderer,
            Constants::clearColor.x,
            Constants::clearColor.y,
            Constants::clearColor.z,
            Constants::clearColor.w
        );
        SDL_RenderClear(renderer);
        
        /* Draw all physical entities */
        if (textureDraw)
        {
            drawEntities();
        }

        /* Draw wireframe if in debug mode */
        if (debugDraw)
        {
            drawWireframe();
        }

        /* Swap buffers */
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

    void RenderSystem::drawWireframe()
    {
        SDL_SetRenderDrawColor
        (
            renderer,
            Constants::debugDrawColor.x,
            Constants::debugDrawColor.y,
            Constants::debugDrawColor.z,
            Constants::debugDrawColor.w
        );
        
        for (auto& vector : Game::instance->blocks)
        {
            for (auto& block : vector)
            {
                drawWireframeQuad(block->transform->getPositionCameraSpace(), block->transform->getScaleCameraSpace());
            }
        }
    }

    void RenderSystem::drawWireframeQuad(glm::vec2 position, glm::vec2 scale)
    {
        textureRect->x = position.x;
        textureRect->y = position.y;
        textureRect->w = scale.x;
        textureRect->h = scale.y;

        SDL_RenderDrawRect(renderer, textureRect);
    }
}