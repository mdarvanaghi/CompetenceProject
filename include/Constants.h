#pragma once

#include <string>
#include "glm/glm/glm.hpp"
namespace Motherload
{
    namespace Constants
    {
        /* Window */
        const float intitialWindowHeight = 720;
        const float intitialWindowWidth = 1280;
        const glm::vec4 clearColor = glm::vec4(0, 40, 130, 0);
        
        /* Blocks */
        const float cellSize = 40;
        const int worldDepth = 50;
        const float spawnChanceGranite = 0.1;
        const float spawnChanceIron = 0.05;
        const float spawnChanceGold = 0.005;

        /* Debug */
        const float cameraSpeed = 300;
        const glm::vec4 debugQuadColor(0, 155, 20, 0);
        const glm::vec4 debugCircleColor(255, 0, 0, 0);
        const glm::vec4 debugLineColor(0, 0, 255, 0);
        const int debugVertexCount = 8;
    } // namespace Constants
} // namespace Motherload
