#pragma once

#include "glm/glm/glm.hpp"
#include "Components/Collider.h"
#include "Systems/Physics/Collision.h"

namespace Motherload
{
    namespace Physics
    {
        class PhysicsSystem
        {
        private:
            static Collision* detectCollision(Collider* a, Collider* b);
            static void resolveCollision();
        public:
            static void step(float deltaTime);
            static Physics::Collision* detectCollisions();
            static void resolveCollisions();
        };
    } // namespace Physics
} // namespace Motherload