#pragma once

#include "SDL.h"
#include <vector>
#include <algorithm>
#include <string>
#include "Systems/RenderSystem.h"
#include "Systems/UI/UIPanel.h"

namespace Motherload
{
    struct UIPanel;

    class UISystem
    {
    private:
        static std::vector<int> panelsToBeRemoved;

        static void updateDepthMeters();
        static void clearPanels();
    public:
        static std::vector<UIPanel*> panels;

        static void initialize();
        static void update(float deltaTime);
        static UIPanel* addPanel(glm::vec2 position, const char* text = "", bool centered = false);
        static UIPanel* addPanel(glm::vec2 position, const char* text = "", const char* fontFamily = Constants::uiFont, bool centered = false);
        static UIPanel* addPanel(UIPanel* panel, const char* text);
        static void removePanel(UIPanel* panel);
    };
} // namespace Motherload