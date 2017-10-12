#pragma once

#include "Entities/PhysicalEntity.h"
#include "glm/glm/glm.hpp"

namespace Motherload
{
    class Player : public PhysicalEntity
    {
    public:
        Player(glm::vec2 position);
    };
} // namespace Motherload
