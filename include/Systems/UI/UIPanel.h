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
        bool active;
        const char* text;

    public:
        SDL_Texture* backgroundPanel;
        SDL_Texture* texture;
        float padding;
        glm::vec2 position;
        glm::vec2 size;
        bool centered;

        UIPanel(glm::vec2 position, bool centered, const char* fontFamily);
        void setBackgroundPanel(SDL_Texture* texture, float padding = 5.0f);
        void setText(const char* text);
        void setActive(bool value);
    };
} // namespace Motherload