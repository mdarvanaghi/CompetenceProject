#include "Systems/UI/UIPanel.h"

namespace Motherload
{
    UIPanel::UIPanel(glm::vec2 position, bool centered,  const char* fontFamily, int wrapAfterPixels)
    {
        this->backgroundPanel = nullptr;
        this->texture = nullptr;
        this->text = std::vector<std::string>();
        this->padding = 0.0f;
        this->position = position;
        this->size = size;
        this->centered = centered;
        this->font = ResourceManager::getFont(fontFamily);
        this->active = true;
        this->wrapAfterPixels = wrapAfterPixels;
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

    void UIPanel::setText(std::vector<std::string> textStrings, SDL_Color textColor)
    {
        this->text = textStrings;
        int height;
        int width = 0;
        std::string combinedString = "";
        for (auto& text : textStrings)
        {
            int textWidth;
            TTF_SizeText(font, text.c_str(), &textWidth, &height);
            if (textWidth > width)
            {
                width = textWidth;
            }
            combinedString += text + "\n";
        }
        height *= textStrings.size();
        const char* cString = combinedString.c_str();

        size = glm::vec2(width, height);
        surface = TTF_RenderText_Blended_Wrapped(font, cString, textColor, width);
        if (texture != nullptr)
        {
            SDL_DestroyTexture(texture);
        }
        texture = RenderSystem::createSurfaceTexture(surface);
        SDL_FreeSurface(surface);
    }

    void UIPanel::setText(std::string text, SDL_Color textColor)
    {
        std::vector<std::string> textStrings = std::vector<std::string>();
        textStrings.push_back(text);
        setText(textStrings, textColor);
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
