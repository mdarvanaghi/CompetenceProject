#pragma once

#include "SDL.h"
#include "Systems/InputSystem.h"
#include "Systems/RenderSystem.h"

namespace Motherload
{
    class DebugSystem
    {
    public:
        // Variables
        static bool debugMode;

        // Methods
        static void initialize();
        static void update();
        static void addDebugLine(glm::vec2 a, glm::vec2 b, glm::vec4 color = Constants::debugLineColor, float time = 2.0f);
        static void addDebugLine(glm::vec2 position, glm::vec2 direction, float length, glm::vec4 color = Constants::debugLineColor, float time = 2.0f);
    };
} // namespace Motherload
