#pragma once

#include "glm/glm/glm.hpp"

namespace Motherload
{
    struct Transform
    {
    public:
        glm::vec2 position;
        glm::vec2 scale;

        Transform(glm::vec2 position, glm::vec2 scale);
    };
} // namespace Motherload