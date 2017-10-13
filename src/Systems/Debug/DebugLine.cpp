#include "Systems/Debug/DebugLine.h"

namespace Motherload
{
    DebugLine::DebugLine(glm::vec2 a, glm::vec2 b, glm::vec4 color, float time)
    {
        this->a = a;
        this->b = b;
        this->color = color;
        this->time = time;
    }
} // namespace Motherload