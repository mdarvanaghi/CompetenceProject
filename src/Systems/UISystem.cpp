#include "Systems/UI/UISystem.h"

namespace Motherload
{
    std::vector<UIPanel*> UISystem::panels;
    std::vector<int> UISystem::panelsToBeRemoved;

    void UISystem::initialize()
    {
        panels = std::vector<UIPanel*>();
    }

    void UISystem::update(float deltaTime)
    {
        /* Update depth meters */
        updateDepthMeters();

        clearPanels();
    }

    void UISystem::updateDepthMeters()
    {
        int currentDepth = int (Game::instance->player->transform->positionWorldSpace.y);
        std::string depthString = "Depth: " + std::to_string(currentDepth);
        Game::instance->depthPanel->setText(depthString.c_str());

        if (currentDepth > Game::instance->lowestDepth)
        {
            Game::instance->lowestDepth = currentDepth;
            std::string lowestDepthString = "Lowest depth: " + std::to_string(Game::instance->lowestDepth);
            Game::instance->lowestDepthPanel->setText(lowestDepthString.c_str());
        }
    }

    UIPanel* UISystem::addPanel(glm::vec2 position, const char* text, bool centered)
    {
        return addPanel(position, text, Constants::debugFont, centered);
    }

    UIPanel* UISystem::addPanel(glm::vec2 position, const char* text, const char* fontFamily, bool centered)
    {
        UIPanel* panel = new UIPanel(position, centered, fontFamily);
        return addPanel(panel, text);
    }

    UIPanel* UISystem::addPanel(UIPanel* panel, const char* text)
    {
        panel->setText(text);
        panels.push_back(panel);
        return panel;
    }

    void UISystem::removePanel(UIPanel* panel)
    {
        int i = 0;
        for (auto& element : panels) 
        {
            if (element == panel)
            {
                panelsToBeRemoved.push_back(i);
            }
            i++;
        }   
    }

    void UISystem::clearPanels()
    {
        std::sort(panelsToBeRemoved.begin(), panelsToBeRemoved.end());

        int index = 0;
        
        while (panelsToBeRemoved.size() > 0) 
        {
            index = panelsToBeRemoved.back();
            panels.erase(panels.begin() + index);
            panelsToBeRemoved.pop_back();
        }
    }

} // namespace Motherload

