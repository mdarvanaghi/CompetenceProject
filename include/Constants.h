#pragma once

#include <string>
#include "SDL.h"
#include "glm/glm/glm.hpp"
namespace Motherload
{
    namespace Constants
    {
        /* Window */
        const float intitialWindowHeight = 720;
        const float intitialWindowWidth = 1280;
        const glm::vec2 midScreen = glm::vec2(intitialWindowWidth / 2, intitialWindowHeight / 2);
        
        /* Player */
        const float playerAccelerationX = 10.0f;
        const float playerDecelerationX = 1.0f;
        const float playerAccelerationY = 20.0f;
        const float playerMaxSpeedX = 5.0f;
        const float playerTerminalVelocity = 9.0f; 
        const float gravity = 9.82f;
        const float drillTime = 1.0f;
        
        /* Blocks */
        const float cellSize = 40;
        const int worldDepth = 50;
        const float spawnChanceGranite = 0.1;
        const float spawnChanceIron = 0.05;
        const float spawnChanceGold = 0.005;
        
        /* Debug */
        const float cameraSpeed = 300;
        const glm::vec4 debugQuadColor(0, 155, 20, 0);
        const glm::vec4 debugNeighborQuadColor(155, 20, 20, 0);
        const glm::vec4 debugCircleColor(255, 0, 0, 0);
        const glm::vec4 debugLineColor(0, 0, 255, 0);
        const glm::vec4 debugPenetrationColor(140, 140, 0, 0);
        const int debugVertexCount = 8;
        static const char* debugFont = "data/fonts/VCR_OSD_MONO_1.001.ttf";
        const glm::vec2 fpsPanelPosition(intitialWindowWidth - intitialWindowWidth / 5, 30);
        
        /* Physics */
        const float baseImpulse = 60.0f;
        const float correctionPercent = 0.2f;
        const float correctionSlop = 0.01f;
        const glm::vec2 up = glm::vec2(0.0f, -1.0f);
        const glm::vec2 down = glm::vec2(0.0f, 1.0f);
        const glm::vec2 left = glm::vec2(-1.0f, 0.0f);
        const glm::vec2 right = glm::vec2(1.0f, 0.0f);
        
        /* UI */
        const glm::vec2 moneyPanelPosition(intitialWindowWidth / 2, 40);
        const glm::vec2 inventoryPanelPosition(40, intitialWindowHeight / 2);
        const glm::vec2 granitePanelPosition(40, intitialWindowHeight / 2 + cellSize);
        const glm::vec2 ironPanelPosition(40, intitialWindowHeight / 2 + cellSize * 2);
        const glm::vec2 goldPanelPosition(40, intitialWindowHeight / 2 + cellSize * 3);
        const SDL_Color textColor = {100, 255, 100, 255};
        static const char* uiFont = "data/fonts/Capture_it.ttf";
        const int fontSize = 20;
        
        /* Clear colors */
        const glm::vec4 firstClearColor(0, 40, 130, 1);
        const glm::vec4 secondClearColor(80, 80, 80, 1);
        
    } // namespace Constants
} // namespace Motherload
