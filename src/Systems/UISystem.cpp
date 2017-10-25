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
        removeFlaggedPanels();
    }

    UIPanel* UISystem::addPanel(glm::vec2 position, std::string text, bool centered)
    {
        return addPanel(position, text, Constants::debugFont, centered);
    }

    UIPanel* UISystem::addPanel(glm::vec2 position, std::string text, const char* fontFamily, bool centered)
    {
        UIPanel* panel = new UIPanel(position, centered, fontFamily);
        return addPanel(panel, text);
    }

    UIPanel* UISystem::addPanel(UIPanel* panel, std::string text)
    {
        panel->setText(text);
        panels.push_back(panel);
        return panel;
    }

    UIPanel* UISystem::addPanel(glm::vec2 position, std::vector<std::string> textStrings, bool centered)
    {
        return addPanel(position, textStrings, Constants::debugFont, centered);
    }

    UIPanel* UISystem::addPanel(glm::vec2 position, std::vector<std::string> textStrings, const char* fontFamily, bool centered)
    {
        UIPanel* panel = new UIPanel(position, centered, fontFamily);
        return addPanel(panel, textStrings);
    }

    UIPanel* UISystem::addPanel(UIPanel* panel, std::vector<std::string> textStrings)
    {
        panel->setText(textStrings);
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

    void UISystem::removeFlaggedPanels()
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

