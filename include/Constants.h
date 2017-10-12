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
        const glm::vec4 debugDrawColor(0, 155, 20, 0);
    } // namespace Constants
} // namespace Motherload
