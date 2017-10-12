#include "Components/Collider.h"

namespace Motherload
{
    Collider::Collider(Entity* entity)
    {
        this->entity = entity;
        float halfWidth = entity->transform->sizeWorldSpace.x / 2.0f;
        float halfHeight = entity->transform->sizeWorldSpace.y / 2.0f; 
        this->topLeft = glm::vec2(-halfWidth, -halfHeight);
        this->bottomRight = glm::vec2(halfWidth - halfHeight);
    }

    glm::vec2 Collider::getTopLeft()
    {
        return this->entity->transform->positionWorldSpace + this->topLeft;
    }

    glm::vec2 Collider::getBottomRight()
    {
        return this->entity->transform->positionWorldSpace + this->bottomRight;
    }
} // namespace Motherload