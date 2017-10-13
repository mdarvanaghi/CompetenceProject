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

    void DebugSystem::addDebugLine(glm::vec2 a, glm::vec2 b, glm::vec4 color, float time)
    {
        RenderSystem::addDebugLine(new DebugLine(a, b, color, time));
    }

    void DebugSystem::addDebugLine(glm::vec2 position, glm::vec2 direction, float length, glm::vec4 color, float time)
    {
        glm::vec2 b = position + direction * length;
        addDebugLine(position, b, color, time);
    }
} // namespace Motherload