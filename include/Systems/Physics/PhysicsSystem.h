#pragma once

#include "glm/glm.hpp"
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
            static std::vector<Collision*> collisions;
            static Collision* detectCollision(Collider* a, Collider* b);
            static void resolveCollision(Collision* collision, float deltaTime);
        public:
            static void initialize();
            static void step(float scaledDeltaTime);
            static void detectCollisions();
            static void resolveCollisions(float scaledDeltaTime);
        };
    } // namespace Physics
} // namespace Motherload