#pragma once

#include "SDL.h"
#include <vector>
#include <algorithm>
#include <string>
#include "Systems/UI/UIPanel.h"

namespace Motherload
{
    struct UIPanel;
    class RenderSystem;

    class UISystem
    {
    private:
        static std::vector<int> panelsToBeRemoved;

        static void updateDepthMeters();
        static void removeFlaggedPanels();
    public:
        static std::vector<UIPanel*> panels;

        static void initialize();
        static void update(float deltaTime);
        // Single line overloads
        static UIPanel* addPanel(glm::vec2 position, std::string text = "", bool centered = false);
        static UIPanel* addPanel(glm::vec2 position, std::string text = "", const char* fontFamily = Constants::debugFont, bool centered = false);
        static UIPanel* addPanel(UIPanel* panel, std::string text);
        // Multiple line overloads
        static UIPanel* addPanel(glm::vec2 position, std::vector<std::string> textStrings, bool centered);
        static UIPanel* addPanel(glm::vec2 position, std::vector<std::string> textStrings, const char* fontFamily, bool centered);
        static UIPanel* addPanel(UIPanel* panel, std::vector<std::string> textStrings);
        static void removePanel(UIPanel* panel);
    };
} // namespace Motherload
