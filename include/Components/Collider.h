#pragma once

#include "glm/glm/glm.hpp"

namespace Motherload
{
    namespace Physics
    {
        class Collider
        {
        public:
            glm::vec2 topLeft;
            glm::vec2 bottomRight;
        };
    }
} // namespace Motherload