#pragma once

#include <string>
#include <iostream>
#include "SDL_image.h"
#include "glm/glm/glm.hpp"
#include "Constants.h"
#include "Game.h"

namespace Motherload
{
    class RenderSystem
    {
    private:
        static SDL_Rect* textureRect;
        static SDL_Renderer* renderer;
        static void drawWireframeQuad(glm::vec2 position, glm::vec2 scale);

    public:
        static bool debugDraw;
        static bool textureDraw;

        static SDL_Texture* loadTexture(const std::string &file);
        static void renderTexture(SDL_Texture *texture, glm::vec2 position, glm::vec2 scale);
        static void initialize(SDL_Window* window);
        static void renderScene();
        static void drawEntities();
        static void drawWireframe();
    };
} // namespace Motherload
