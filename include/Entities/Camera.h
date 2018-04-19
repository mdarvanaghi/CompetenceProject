#pragma once

#include "glm/glm.hpp"

namespace Motherload
{
    // Forward declarations
    class DebugSystem;

    class Camera
    {
    public:
        static void initialize();
        static void updatePosition(float deltaTime);
        static glm::vec2 positionWorldSpace;

        static glm::vec2 toCameraSpace(glm::vec2 position);
    };
} // namespace Motherload
