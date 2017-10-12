#pragma once

#include "glm/glm/glm.hpp"
#include "Entities/Entity.h"
#include "Components/Collider.h"

namespace Motherload
{
    namespace Physics
    {
        class PhysicsEntity : public Entity
        {
        public:
            Physics::Collider collider;
        }; 
    } // namespace Physics
} // namespace Motherload
