#pragma once

#include "glm/glm/glm.hpp"

namespace Extensions
{
    namespace Vector2
    {
        static glm::vec2 lerp(glm::vec2 a, glm::vec2 b, float t)
        {
            return b * t + a * (1.0f - t);
        }
    } // namespace Vector2
} // namespace Extensions