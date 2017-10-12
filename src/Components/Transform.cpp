#include "Components/Transform.h"

namespace Motherload
{
    Transform::Transform(glm::vec2 position, glm::vec2 size, glm::vec2 scale)
    {
        this->positionWorldSpace = position;
        this->sizeWorldSpace = size;
        this->scaleWorldSpace = scale;
    }

    glm::vec2 Transform::getPositionCameraSpace()
    {
        return positionWorldSpace - Camera::positionWorldSpace;
    }

    glm::vec2 Transform::getSizeCameraSpace()
    {
        // TODO: Maybe implement zoom if fitting
        return sizeWorldSpace * scaleWorldSpace;
    }

} // namespace Motherload
