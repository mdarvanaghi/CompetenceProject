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
        
        /* Draw all entities */
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
                renderTexture
                (
                    block->texture,
                    block->transform->getPositionCameraSpace() - (block->transform->sizeWorldSpace / 2.0f),
                    block->transform->getSizeCameraSpace()
                );
            }
        }
    }

    void RenderSystem::drawWireframe()
    {       
        for (auto& vector : Game::instance->blocks)
        {
            for (auto& block : vector)
            {
                drawWireframeQuad
                (
                    block->transform->getPositionCameraSpace() - (block->transform->sizeWorldSpace / 2.0f),
                    block->transform->getSizeCameraSpace()
                );

                drawWireframeCircle(block->transform->getPositionCameraSpace());
            }
        }
    }

    void RenderSystem::drawWireframeQuad(glm::vec2 position, glm::vec2 scale)
    {
        SDL_SetRenderDrawColor
        (
            renderer,
            Constants::debugQuadColor.x,
            Constants::debugQuadColor.y,
            Constants::debugQuadColor.z,
            Constants::debugQuadColor.w
        );
        
        textureRect->x = position.x;
        textureRect->y = position.y;
        textureRect->w = scale.x;
        textureRect->h = scale.y;

        SDL_RenderDrawRect(renderer, textureRect);
    }

    void RenderSystem::drawWireframeCircle(glm::vec2 position, float radius) 
    {
        SDL_SetRenderDrawColor
        (
            renderer,
            Constants::debugCircleColor.x,
            Constants::debugCircleColor.y,
            Constants::debugCircleColor.z,
            Constants::debugCircleColor.w
        );

        glm::vec2 points[Constants::debugVertexCount];

        for(int i = 0; i < Constants::debugVertexCount; i++)
        {
            points[i] = position + glm::vec2(glm::cos(i * (2 * glm::pi<float>() / (float) Constants::debugVertexCount )) * radius, glm::sin(i * (2 * glm::pi<float>() / (float) Constants::debugVertexCount)) * radius);
        }

        for(int i = 0; i < Constants::debugVertexCount-1; i++)
        {
            SDL_RenderDrawLine
            (
                renderer,
                points[i].x,
                points[i].y, 
                points[i+1].x,
                points[i+1].y
            ); 
        }

        SDL_RenderDrawLine
        (
            renderer,
            points[Constants::debugVertexCount-1].x,
            points[Constants::debugVertexCount-1].y, 
            points[0].x,
            points[0].y
        ); 
    }
}