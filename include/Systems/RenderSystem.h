#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "SDL_image.h"
#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp"
#include "Constants.h"
#include "Game.h"
#include "Systems/Debug/DebugLine.h"
#include "Systems/UI/UISystem.h"

namespace Motherload
{
    class RenderSystem
    {
    private:
        static SDL_Renderer* renderer;
        static SDL_Rect* textureRect;
        static void renderTexture(SDL_Texture *texture, glm::vec2 position, glm::vec2 scale);
        static void drawEntities();
        static void drawUIPanels();
        static void setDrawingColor(glm::vec4 color);
        
        /* Debugging */
        static std::vector<DebugLine*> debugLines;
        static std::vector<int> debugLinesToBeRemoved;
        static void drawWireframe();
        static void drawWireframeQuad(glm::vec2 position, glm::vec2 scale, glm::vec4 = Constants::debugQuadColor);
        static void drawWireframeCircle(glm::vec2 position, float radius = 5.0f);
        static void drawLine(DebugLine* line);
        static void clearDebugLines();
        static void setClearColor(glm::vec4 color);
        static void updateClearColor();
        
    public:
        // Variables
        static bool debugDraw;
        static bool textureDraw;
        static bool uiDraw;

        // Methods
        static SDL_Texture* loadTexture(const std::string &file);
        static SDL_Texture* createSurfaceTexture(SDL_Surface* surface);
        static void initialize(SDL_Window* window);
        static void renderScene();
        static void addDebugLine(DebugLine* line);
    };
} // namespace Motherload
