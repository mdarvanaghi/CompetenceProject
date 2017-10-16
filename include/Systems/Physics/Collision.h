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
            PhysicsEntity* a;
            PhysicsEntity* b;
            glm::vec2 normal;
            float penetration;

            Collision
            (
                PhysicsEntity* a,
                PhysicsEntity* b,
                glm::vec2 normal,
                float penetration
            );
        };
    } // namespace Physics
} // namespace Motherload