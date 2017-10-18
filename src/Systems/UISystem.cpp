#include "Systems/UI/UISystem.h"

namespace Motherload
{
    std::vector<UIPanel*> UISystem::panels;

    void UISystem::initialize()
    {
        panels = std::vector<UIPanel*>();
    }

    UIPanel* UISystem::addPanel(glm::vec2 position, const char* text, bool centered)
    {
        return addPanel(position, text, Constants::uiFont, centered);
    }

    UIPanel* UISystem::addPanel(glm::vec2 position, const char* text, const char* fontFamily, bool centered)
    {
        UIPanel* panel = new UIPanel(position, centered, fontFamily);
        panel->setText(text);
        panels.push_back(panel);
        return panel;
    }

    void UISystem::removePanel(UIPanel* panel)
    {
        // TODO: Implement panel removal
    }

} // namespace Motherload

