#pragma once

#include <string>
#include <iostream>
#include "SDL_image.h"
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/constants.hpp"
#include "Constants.h"
#include "Game.h"

namespace Motherload
{
    class RenderSystem
    {
    private:
        static SDL_Rect* textureRect;
        static SDL_Renderer* renderer;
        static void renderTexture(SDL_Texture *texture, glm::vec2 position, glm::vec2 scale);
        static void drawEntities();
        static void drawWireframe();
        static void drawWireframeQuad(glm::vec2 position, glm::vec2 scale);
        static void drawWireframeCircle(glm::vec2 position, float radius = 5.0f);

    public:
        // Variables
        static bool debugDraw;
        static bool textureDraw;

        // Methods
        static SDL_Texture* loadTexture(const std::string &file);
        static void initialize(SDL_Window* window);
        static void renderScene();
    };
} // namespace Motherload
