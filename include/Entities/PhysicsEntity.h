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
            // Variables
            Collider* collider;
            bool isDynamic;
            float maxSpeedX, maxSpeedY;
            glm::vec2 velocity;

            // Methods
            virtual void physicsUpdate(float deltaTime) {}
        }; 
    } // namespace Physics
} // namespace Motherload
