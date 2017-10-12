#pragma once

#include "glm/glm/glm.hpp"
#include "Components/Component.h"
#include "Entities/Entity.h"

namespace Motherload
{
    class Collider : public Component
    {
    private:
        glm::vec2 topLeft;
        glm::vec2 bottomRight;
    public:
        Collider(Entity* entity);
        glm::vec2 getTopLeft();
        glm::vec2 getBottomRight();
    };
} // namespace Motherload