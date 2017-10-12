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
            Physics::PhysicsEntity* a;
            Physics::PhysicsEntity* b;
            glm::vec2 normal;
            float penetration;

            Collision
            (
                Physics::PhysicsEntity* a,
                Physics::PhysicsEntity* b,
                glm::vec2 normal,
                float penetration
            );
        };
    } // namespace Physics
} // namespace Motherload