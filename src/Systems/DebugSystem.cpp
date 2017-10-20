#include "Systems/DebugSystem.h"

namespace Motherload
{
    // Forward declarations
    bool DebugSystem::debugMode;
    bool DebugSystem::detachedCamera;


    // Static variables
    UIPanel* DebugSystem::fpsPanel;
    void DebugSystem::initialize()
    {
        // TODO: Change at compile-time instead
        debugMode = true;
        detachedCamera = false;
        RenderSystem::debugDraw = false;
        RenderSystem::textureDraw = true;
        RenderSystem::uiDraw = true;

        if (debugMode)
        {
            fpsPanel = UISystem::addPanel(Constants::fpsPanelPosition, "FPS: ", Constants::debugFont);
        }
    }

    void DebugSystem::update(float deltaTime)
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

        /* Update FPS meter */
        fpsPanel->setText(("FPS: " + std::to_string(1 / deltaTime)).c_str());

        if (InputSystem::getKeyDown(SDL_SCANCODE_F8))
        {
            RenderSystem::uiDraw = !RenderSystem::uiDraw;
        }

        if (InputSystem::getKeyDown(SDL_SCANCODE_F9))
        {
            detachedCamera = !detachedCamera;
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