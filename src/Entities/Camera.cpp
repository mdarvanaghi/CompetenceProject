#include "Entities/Camera.h"
#include "Systems/InputSystem.h"
#include "Game.h"

namespace Motherload
{
    glm::vec2 Camera::positionWorldSpace;
    void Camera::initialize()
    {
        positionWorldSpace = glm::vec2(0);
    }

    void Camera::updatePosition()
    {
        if (!DebugSystem::debugMode)
        {
            return;
        }
        if (InputSystem::getKey(SDL_SCANCODE_W))
        {
            positionWorldSpace.y -= 5;
        }
        if (InputSystem::getKey(SDL_SCANCODE_A))
        {
            positionWorldSpace.x -= 5;
        }
        if (InputSystem::getKey(SDL_SCANCODE_S))
        {
            positionWorldSpace.y += 5;
        }
        if (InputSystem::getKey(SDL_SCANCODE_D))
        {
            positionWorldSpace.x += 5;
        }
    }
} // namespace Motherload
