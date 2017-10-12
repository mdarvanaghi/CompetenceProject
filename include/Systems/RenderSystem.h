#pragma once

#include <string>
#include <iostream>
#include "SDL_image.h"
#include "glm/glm/glm.hpp"

namespace Motherload
{
    class RenderSystem
    {
    private:
        SDL_Rect* textureRect;
        SDL_Texture* texture;
        static SDL_Renderer* renderer;

    public:
        static SDL_Texture* loadTexture(const std::string &file);
        void renderTexture(SDL_Texture *texture, glm::vec2 position, glm::vec2 scale);
        void initialize(SDL_Window* window);
        void renderScene();
        void drawEntities();
    };
}
