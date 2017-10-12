#pragma once

#include "glm/glm/glm.hpp"
#include "Components/Transform.h"
#include "Entities/Entity.h"

namespace Motherload
{
    class Camera
    {
    public:
        static void initialize();
        static void updatePosition();
        static glm::vec2 positionWorldSpace;
    };
} // namespace Motherload