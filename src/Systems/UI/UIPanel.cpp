#include "Systems/UI/UIPanel.h"

namespace Motherload
{
    UIPanel::UIPanel(glm::vec2 position, bool centered,  const char* fontFamily)
    {
        this->position = position;
        this->size = size;
        this->centered = centered;
        this->font = ResourceManager::getFont(fontFamily);
        if (this->font == nullptr)
        {
            std::cout << fontFamily << " could not be loaded" << std::endl;
        }
    }

    void UIPanel::setText(const char* text)
    {
        int width, height;
        TTF_SizeText(font, text, &width, &height);
        size = glm::vec2(width, height);
        surface = TTF_RenderText_Solid(font, text, Constants::textColor);
        texture = RenderSystem::createSurfaceTexture(surface);
        SDL_FreeSurface(surface);
    }
} // namespace Motherload