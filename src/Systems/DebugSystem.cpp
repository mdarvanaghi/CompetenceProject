#include "Systems/DebugSystem.h"

namespace Motherload
{
    // Forward declarations
    bool DebugSystem::debugMode;

    void DebugSystem::initialize()
    {
        // TODO: Change at compile-time instead
        debugMode = true;
    }

    void DebugSystem::update()
    {
        if (InputSystem::getKeyDown(SDL_SCANCODE_F11))
        {
            RenderSystem::debugDraw = !RenderSystem::debugDraw;
        }

        if (InputSystem::getKeyDown(SDL_SCANCODE_F12))
        {
            debugMode = !debugMode;
        }

        if (!debugMode)
        {
            return;
        }
    }
} // namespace Motherload