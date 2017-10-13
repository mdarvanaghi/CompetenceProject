#pragma once

#include "glm/glm/glm.hpp"
#include <vector>
#include "Components/Collider.h"
#include "Systems/Physics/Collision.h"
#include "Game.h"

namespace Motherload
{
    namespace Physics
    {
        class PhysicsSystem
        {
        private:
            static Collision* detectCollision(Collider* a, Collider* b);
            static void resolveCollision(Collision* collision);
        public:
            static void step(float deltaTime);
            static std::vector<Physics::Collision*> detectCollisions();
            static void resolveCollisions(std::vector<Collision*> collisions);
        };
    } // namespace Physics
} // namespace Motherload