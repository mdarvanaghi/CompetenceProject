#pragma once

#include "glm/glm/glm.hpp"

namespace Motherload
{
    struct DebugLine
    {
    public:
        glm::vec2 a;
        glm::vec2 b;
        glm::vec4 color;
        float time;

        DebugLine(glm::vec2 a, glm::vec2 b, glm::vec4 color, float time);
    };
} // namespace Motherload   