#pragma once

#include "Entities/PhysicsEntity.h"
#include "glm/glm/glm.hpp"

namespace Motherload
{
    class Player : public Physics::PhysicsEntity
    {
    public:
        Player(glm::vec2 position);
    };
} // namespace Motherload
