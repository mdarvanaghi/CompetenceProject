#pragma once

#include "SDL.h"
#include "Systems/InputSystem.h"
#include "Systems/RenderSystem.h"
#include "Systems/UI/UISystem.h"
#include "Systems/UI/UIPanel.h"

namespace Motherload
{
    class DebugSystem
    {
    private:
        static UIPanel* fpsPanel;
    public:
        // Variables
        static bool debugMode;
        static bool detachedCamera;

        // Methods
        static void initialize();
        static void update(float deltaTime);
        static void addDebugLine(glm::vec2 a, glm::vec2 b, glm::vec4 color = Constants::debugLineColor, float time = 0.0f);
        static void addDebugLine(glm::vec2 position, glm::vec2 direction, float length, glm::vec4 color = Constants::debugLineColor, float time = 0.0f);
    };
} // namespace Motherload
