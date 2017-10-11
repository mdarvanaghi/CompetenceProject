#include "Components/Transform.h"

namespace Motherload
{
    Transform::Transform(glm::vec2 position, glm::vec2 scale)
    {
        this->position = position;
        this->scale = scale;
    }
} // namespace Motherload
