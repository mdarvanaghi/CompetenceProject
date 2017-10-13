#pragma once

#include "Entities/PhysicsEntity.h"
#include "glm/glm/glm.hpp"

namespace Motherload
{
    namespace Physics
    {
        struct Collision
        {
        public:
            Entity* a;
            Entity* b;
            glm::vec2 normal;
            float penetration;

            Collision
            (
                Entity* a,
                Entity* b,
                glm::vec2 normal,
                float penetration
            );
        };
    } // namespace Physics
} // namespace Motherload