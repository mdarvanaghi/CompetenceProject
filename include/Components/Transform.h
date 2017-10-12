#pragma once

#include "glm/glm/glm.hpp"
#include "Constants.h"
#include "Entities/Camera.h"

namespace Motherload
{
    struct Transform
    {
    private:
        bool dirty = false;
        glm::vec2 positionWorldSpace;
        glm::vec2 scaleWorldSpace;
    public:
        glm::vec2 sizeWorldSpace;

        Transform(glm::vec2 position, glm::vec2 size = glm::vec2(Constants::cellSize, Constants::cellSize), glm::vec2 scale = glm::vec2(1));
        glm::vec2 getPositionCameraSpace();
        glm::vec2 getSizeCameraSpace();
        glm::vec2 getScaleCameraSpace();
    };
} // namespace Motherload