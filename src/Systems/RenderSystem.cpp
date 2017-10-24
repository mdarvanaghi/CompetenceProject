#include "Systems/RenderSystem.h"

namespace Motherload
{
    SDL_Renderer* RenderSystem::renderer;
    SDL_Rect* RenderSystem::textureRect;

    std::vector<DebugLine*> RenderSystem::debugLines;
    std::vector<int> RenderSystem::debugLinesToBeRemoved;

    bool RenderSystem::debugDraw;
    bool RenderSystem::textureDraw;
    bool RenderSystem::uiDraw;

    void RenderSystem::initialize(SDL_Window* window)
    {
        textureRect = new SDL_Rect();
        
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer == nullptr)
        {
            std::cerr << "Could not create SDL Renderer." << std::endl;
        }

        setClearColor(Constants::firstClearColor);
    }

    void RenderSystem::setClearColor(glm::vec4 color)
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

    SDL_Texture* RenderSystem::loadTexture(const std::string &file)
    {
        SDL_Texture* texture = IMG_LoadTexture(renderer, file.c_str());
        if (texture == nullptr)
        {
            std::cerr << "Texture load error!" << std::endl;
        }
        return texture;
    }

    SDL_Texture* RenderSystem::createSurfaceTexture(SDL_Surface* surface)
    {
        return SDL_CreateTextureFromSurface(renderer, surface);
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
        updateClearColor();
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

        /* Lastly, draw all UI Panels */
        if (uiDraw)
        {
            drawUIPanels();
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

    void RenderSystem::drawUIPanels()
    {
        for (auto& panel : UISystem::panels)
        {
            /* Render background panel first */
            if (panel->backgroundPanel != nullptr)
            {
                renderTexture
                (
                    panel->backgroundPanel,
                    panel->centered ? panel->position - (panel->size / 2.0f + panel->padding) : panel->position - panel->padding,
                    panel->size + panel->padding * 2
                );
            }

            /* Then render the text */
            if (panel->texture == nullptr)
            {
                std::cerr << "UI Panel texture is nullptr" << std::endl;
                continue;
            }

            renderTexture
            (
                panel->texture,
                panel->centered ? panel->position - panel->size / 2.0f : panel->position,
                panel->size
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

                // drawWireframeCircle(entity->transform->getPositionCameraSpace());
        }

        for (auto& vector : Game::instance->player->neighbors)
        {
            for (auto& entity : vector)
            {
                if (entity == nullptr)
                {
                    continue;
                }
                drawWireframeQuad
                (
                    entity->transform->getPositionCameraSpace() - (entity->transform->sizeWorldSpace / 2.0f),
                    entity->transform->getSizeCameraSpace(),
                    Constants::debugNeighborQuadColor
                );
            }
        }
        // if 
        // (
        //     Game::instance->player->neighbors[2][1] != nullptr &&
        //     Game::instance->player->neighbors[1][0] != nullptr &&
        //     Game::instance->player->neighbors[1][2] != nullptr
        // )
        // drawWireframeQuad
        // (
        //     Game::instance->player->neighbors[2][1]->transform->getPositionCameraSpace() - (Game::instance->player->neighbors[2][1]->transform->sizeWorldSpace / 2.0f),
        //     Game::instance->player->neighbors[2][1]->transform->getSizeCameraSpace(),
        //     Constants::debugNeighborQuadColor
        // );
        // drawWireframeQuad
        // (
        //     Game::instance->player->neighbors[1][0]->transform->getPositionCameraSpace() - (Game::instance->player->neighbors[1][0]->transform->sizeWorldSpace / 2.0f),
        //     Game::instance->player->neighbors[1][0]->transform->getSizeCameraSpace(),
        //     Constants::debugNeighborQuadColor
        // );
        // drawWireframeQuad
        // (
        //     Game::instance->player->neighbors[1][2]->transform->getPositionCameraSpace() - (Game::instance->player->neighbors[1][2]->transform->sizeWorldSpace / 2.0f),
        //     Game::instance->player->neighbors[1][2]->transform->getSizeCameraSpace(),
        //     Constants::debugNeighborQuadColor
        // );

        int lineIndex = 0;
        for (auto& line : debugLines)
        {
            drawLine(line);
            if (line->time <= 0.0f)
            {
                debugLinesToBeRemoved.push_back(lineIndex);
            }
            else
            {
                line->time -= Game::instance->deltaTime;
            }
        }

        clearDebugLines();
    }

    void RenderSystem::drawWireframeQuad(glm::vec2 position, glm::vec2 scale, glm::vec4 color)
    {
        setDrawingColor(color);
        
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
        std::sort(debugLinesToBeRemoved.begin(), debugLinesToBeRemoved.end());
        
        int index = 0;
        while (debugLinesToBeRemoved.size() > 0) 
        {
            index = debugLinesToBeRemoved.back();
            debugLines.erase(debugLines.begin() + index);
            debugLinesToBeRemoved.pop_back();
        }
    }

    void RenderSystem::updateClearColor()
    {
        float currentPlayerDepth = Game::instance->player->transform->positionWorldSpace.y;
        if (currentPlayerDepth <= 0)
        {
            setClearColor(Constants::firstClearColor);
        }
        else if (currentPlayerDepth < Constants::firstColorCutoff)
        {
            setClearColor(Extensions::Vector4::lerp(Constants::firstClearColor, Constants::secondClearColor, currentPlayerDepth / Constants::firstColorCutoff));
        }
        else if (currentPlayerDepth < Constants::secondColorCutoff)
        {
            setClearColor(Extensions::Vector4::lerp(Constants::secondClearColor, Constants::thirdClearColor, (currentPlayerDepth - Constants::firstColorCutoff) * 2 / Constants::secondColorCutoff));
        }
    }
}