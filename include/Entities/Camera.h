#pragma once

#include "glm/glm/glm.hpp"

namespace Motherload
{
    // Forward declarations
    class DebugSystem;

    class Camera
    {
    public:
        static void initialize();
        static void updatePosition();
        static glm::vec2 positionWorldSpace;
    };
} // namespace Motherload