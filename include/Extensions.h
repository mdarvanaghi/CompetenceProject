#pragma once

#include "glm/glm.hpp"

namespace Extensions
{
    namespace Vector2
    {
        static glm::vec2 lerp(glm::vec2 a, glm::vec2 b, float t)
        {
            return b * t + a * (1.0f - t);
        }
    } // namespace Vector2
    namespace Vector4
    {
        static glm::vec4 lerp(glm::vec4 a, glm::vec4 b, float t)
        {
            return b * t + a * (1.0f - t);
        }
    }
} // namespace Extensions