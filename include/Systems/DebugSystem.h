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
    };
} // namespace Motherload
