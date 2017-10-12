#include "Components/Transform.h"

namespace Motherload
{
    Transform::Transform(glm::vec2 position, glm::vec2 scale)
    {
        this->positionWorldSpace = position;
        this->scaleWorldSpace = scale;
    }

    glm::vec2 Transform::getPositionCameraSpace()
    {
        return Camera::positionWorldSpace - positionWorldSpace;
    }

    glm::vec2 Transform::getScaleCameraSpace()
    {
        // TODO: Maybe implement zoom if fitting
        return scaleWorldSpace;
    }

} // namespace Motherload
