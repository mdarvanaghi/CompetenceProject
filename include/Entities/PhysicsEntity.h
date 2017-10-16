#pragma once

#include "glm/glm/glm.hpp"
#include "Entities/Entity.h"
#include "Components/Collider.h"

namespace Motherload
{
    namespace Physics
    {
        class Collider;
        class PhysicsEntity : public Entity
        {
        public:
            // Variables
            Collider* collider;
            float restitution = 1.0f; // Bounciness
            float mass = 1.0f;
            float inverseMass = 1.0 / mass;
            bool isDynamic;
            float maxSpeedX, maxSpeedY;
            glm::vec2 velocity = glm::vec2(0);

            // Methods
            void addForce(glm::vec2 force);
            void setMass(float mass);

            virtual void physicsUpdate(float deltaTime) {}
            virtual void isColliding(PhysicsEntity* other) {}
        }; 
    } // namespace Physics
} // namespace Motherload
