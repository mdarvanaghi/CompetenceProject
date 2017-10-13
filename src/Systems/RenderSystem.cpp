#include "Systems/RenderSystem.h"

namespace Motherload
{
    SDL_Renderer* RenderSystem::renderer;
    SDL_Rect* RenderSystem::textureRect;
    std::vector<DebugLine*> RenderSystem::debugLines;
    std::vector<int> RenderSystem::debugLinesToBeRemoved;
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
        SDL_RenderCopy(renderer, texture, nullptr, textureRect);
    }

    void RenderSystem::renderScene()
    {
        /* Clear renderer */
        setDrawingColor(Constants::clearColor);
        SDL_RenderClear(renderer);
        
        /* Draw all entities */
        if (textureDraw)
        {
            drawEntities();
        }

        /* Draw player after entities */
        // renderTexture(Game::instance->player->texture);

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
        for (auto& entity : Game::instance->entities)
        {
            
            if (entity->texture == nullptr)
            {
                std::cerr << "Texture is nullptr" << std::endl;
            }
            renderTexture
            (
                entity->texture,
                entity->transform->getPositionCameraSpace() - (entity->transform->sizeWorldSpace / 2.0f),
                entity->transform->getSizeCameraSpace()
            );
        }
    }

    void RenderSystem::setDrawingColor(glm::vec4 color)
    {
        SDL_SetRenderDrawColor
        (
            renderer,
            color.x,
            color.y,
            color.z,
            color.w
        );
    }

    void RenderSystem::drawWireframe()
    {       
        for (auto& entity : Game::instance->entities)
        {
                drawWireframeQuad
                (
                    entity->transform->getPositionCameraSpace() - (entity->transform->sizeWorldSpace / 2.0f),
                    entity->transform->getSizeCameraSpace()
                );

                drawWireframeCircle(entity->transform->getPositionCameraSpace());
            
        }

        int lineIndex = 0;
        for (auto& line : debugLines)
        {
            drawLine(line);
            line->time -= Game::instance->deltaTime;
            if (line->time <= 0.0f)
            {
                debugLinesToBeRemoved.push_back(lineIndex);
            }
        }

        clearDebugLines();
    }

    void RenderSystem::drawWireframeQuad(glm::vec2 position, glm::vec2 scale)
    {
        setDrawingColor(Constants::debugQuadColor);
        
        textureRect->x = position.x;
        textureRect->y = position.y;
        textureRect->w = scale.x;
        textureRect->h = scale.y;

        SDL_RenderDrawRect(renderer, textureRect);
    }

    void RenderSystem::drawWireframeCircle(glm::vec2 position, float radius) 
    {
        setDrawingColor(Constants::debugCircleColor);

        glm::vec2 points[Constants::debugVertexCount];

        for (int i = 0; i < Constants::debugVertexCount; i++)
        {
            points[i] = position + glm::vec2(glm::cos(i * (2 * glm::pi<float>() / (float) Constants::debugVertexCount )) * radius, glm::sin(i * (2 * glm::pi<float>() / (float) Constants::debugVertexCount)) * radius);
        }

        for (int i = 0; i < Constants::debugVertexCount-1; i++)
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

    void RenderSystem::drawLine(DebugLine* line)
    {
        setDrawingColor(line->color);

        glm::vec2 posA = line->a - Camera::positionWorldSpace;
        glm::vec2 posB = line->b - Camera::positionWorldSpace;

        SDL_RenderDrawLine
        (
            renderer,
            posA.x,
            posA.y,
            posB.x,
            posB.y
        );
    }

    void RenderSystem::addDebugLine(DebugLine* line)
    {
        debugLines.push_back(line);
    }

    void RenderSystem::clearDebugLines()
    {
        std::sort(debugLinesToBeRemoved.begin(),debugLinesToBeRemoved.end());
        
        int index = 0;
        while (debugLinesToBeRemoved.size() > 0) 
        {
            index = debugLinesToBeRemoved.back();
            debugLines.erase(debugLines.begin() + index);
            debugLinesToBeRemoved.pop_back();
        }
    }
}