#pragma once

#include "SDL.h"
#include <vector>
#include "Systems/RenderSystem.h"
#include "Systems/UI/UIPanel.h"

namespace Motherload
{
    struct UIPanel;

    class UISystem
    {
    public:
        static std::vector<UIPanel*> panels;

        static void initialize();
        static UIPanel* addPanel(glm::vec2 position, const char* text = "", bool centered = false);
        static UIPanel* addPanel(glm::vec2 position, const char* text = "", const char* fontFamily = Constants::uiFont, bool centered = false);
        static void removePanel(UIPanel* panel);
    };
} // namespace Motherload