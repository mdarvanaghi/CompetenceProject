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
            Physics::PhysicsEntity *A;
            Physics::PhysicsEntity *B;
            float penetration;
            glm::vec2 normal;
        };
    } // namespace Physics
} // namespace Motherload