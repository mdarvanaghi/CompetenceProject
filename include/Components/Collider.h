#pragma once

#include "glm/glm/glm.hpp"
#include "Components/Component.h"
#include "Entities/PhysicsEntity.h"

namespace Motherload
{
    namespace Physics
    {
        class PhysicsEntity;
        class Collider : public Component
        {
        private:
            glm::vec2 topLeft;
            glm::vec2 bottomRight;
        public:
            PhysicsEntity* entity;
            Collider(PhysicsEntity* entity);
            glm::vec2 getTopLeft();
            glm::vec2 getBottomRight();
        };
    } // namespace Physics
} // namespace Motherload