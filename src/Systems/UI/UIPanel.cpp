#include "Systems/UI/UIPanel.h"

namespace Motherload
{
    UIPanel::UIPanel(glm::vec2 position, bool centered,  const char* fontFamily)
    {
        this->backgroundPanel = nullptr;
        this->texture = nullptr;
        this->text = nullptr;
        this->padding = 0.0f;
        this->position = position;
        this->size = size;
        this->centered = centered;
        this->font = ResourceManager::getFont(fontFamily);
        if (this->font == nullptr)
        {
            std::cout << fontFamily << " could not be loaded" << std::endl;
        }
    }
    
    void UIPanel::setBackgroundPanel(SDL_Texture* texture, float padding)
    {
        this->backgroundPanel = texture;
        this->padding = padding;
    }

    void UIPanel::setText(const char* text)
    {
        this->text = text;
        int width, height;
        TTF_SizeText(font, text, &width, &height);
        size = glm::vec2(width, height);
        surface = TTF_RenderText_Solid(font, text, Constants::textColor);
        if (texture != nullptr)
        {
            SDL_DestroyTexture(texture);
        }
        texture = RenderSystem::createSurfaceTexture(surface);
        SDL_FreeSurface(surface);
    }

    void UIPanel::setActive(bool value)
    {
        /* Check if status already matches value */
        if (active == value)
        {
            return;
        }
        active = value;
        if (active)
        {
            UISystem::addPanel(this, this->text);
        }
        else 
        {
            UISystem::removePanel(this);
        }
    }
} // namespace Motherload