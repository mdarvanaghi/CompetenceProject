#pragma once

#include <string>
#include <iostream>
#include "SDL_image.h"

namespace Motherload
{
    class RenderSystem
    {
    private:
        SDL_Texture* texture;
        SDL_Renderer* renderer;
    public:
        SDL_Texture* loadTexture(const std::string &file);
        void renderTexture(SDL_Texture *texture, int x, int y, int w, int h);
        void initialize(SDL_Window* window);
        void renderScene();
    };
}
