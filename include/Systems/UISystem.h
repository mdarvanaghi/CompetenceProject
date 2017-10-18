#pragma once

#include "SDL.h"
#include "SDL_ttf.h"
#include "Systems/RenderSystem.h"

namespace Motherload
{
    class UISystem
    {
    private:
        static SDL_Surface* surface;
        static TTF_Font* font;
        
    public:
        static void initialize();
    };
} // namespace Motherload