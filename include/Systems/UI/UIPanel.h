#pragma once

#include "SDL.h"
#include "SDL_ttf.h"
#include "glm/glm/glm.hpp"
#include "Constants.h"
#include "Systems/RenderSystem.h"

namespace Motherload
{
    struct UIPanel
    {
    private:
        SDL_Surface* surface;
        TTF_Font* font;

    public:
        SDL_Texture* texture;
        glm::vec2 position;
        glm::vec2 size;
        bool centered;

        UIPanel(glm::vec2 position, bool centered, const char* fontFamily);
        void setText(const char* text);
    };
} // namespace Motherload