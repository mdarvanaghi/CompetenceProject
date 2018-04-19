#pragma once

#include "SDL.h"
#include "SDL_ttf.h"
#include "glm/glm.hpp"
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
        std::vector<std::string> text;

    public:
        SDL_Texture* backgroundPanel;
        SDL_Texture* texture;
        int wrapAfterPixels;
        float padding;
        glm::vec2 position;
        glm::vec2 size;
        bool centered;

        UIPanel(glm::vec2 position, bool centered, const char* fontFamily, int wrapAfterPixels = 0);
        void setBackgroundPanel(SDL_Texture* texture, float padding = 5.0f);
        void setText(std::string text, SDL_Color textColor = Constants::textColor);
        void setText(std::vector<std::string> text, SDL_Color textColor = Constants::textColor);
        void setActive(bool value);
    };
} // namespace Motherload
