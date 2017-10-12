#include "Systems/DebugSystem.h"

namespace Motherload
{
    // Forward declarations
    bool DebugSystem::debugMode;

    void DebugSystem::initialize()
    {
        // TODO: Change at compile-time instead
        debugMode = true;
        RenderSystem::debugDraw = false;
        RenderSystem::textureDraw = true;
    }

    void DebugSystem::update()
    {
        if (InputSystem::getKeyDown(SDL_SCANCODE_F12))
        {
            debugMode = !debugMode;
            RenderSystem::debugDraw = false;
            RenderSystem::textureDraw = true;
        }

        if (!debugMode)
        {
            return;
        }

        if (InputSystem::getKeyDown(SDL_SCANCODE_F10))
        {
            RenderSystem::textureDraw = !RenderSystem::textureDraw;
        }
        
        if (InputSystem::getKeyDown(SDL_SCANCODE_F11))
        {
            RenderSystem::debugDraw = !RenderSystem::debugDraw;
        }
    }
} // namespace Motherload