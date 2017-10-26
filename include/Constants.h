#pragma once

#include <string>
#include "SDL.h"
#include "glm/glm/glm.hpp"
namespace Motherload
{
    namespace Constants
    {
        /* Window */
        const float initialWindowHeight = 720;
        const float initialWindowWidth = 1280;
        const glm::vec2 midScreen = glm::vec2(initialWindowWidth / 2, initialWindowHeight / 2);
        
        /* Player */
        const float playerAccelerationX = 10.0f;
        const float playerDecelerationX = 1.0f;
        const float playerAccelerationY = 20.0f;
        const float playerMaxSpeedX = 5.0f;
        const float playerTerminalVelocity = 9.0f; 
        const float gravity = 9.82f;
        const float baseDrillTime = 0.5f;
        const float idleFuelRate = 0.8f;
        const float acceleratingFuelRate = 2;
        const float drillingFuelRate = 3;
        const float damageThreshold = 1.2f;
        const float baseDamage = 10;
        const int startMoney = 20;
        
        /* Blocks */
        const float cellSize = 40;
        const int worldDepth = 500;
        // Thresholds
        const int ironThreshold = 10;
        const int silverThreshold = 25;
        const int goldThreshold = 75;
        const int platinumThreshold = 150;
        const int diamondsThreshold = 300;
        // Spawn rates
        const float spawnChanceGranite = 0.1;
        const float spawnChanceIron = 0.02;
        const float spawnChanceSilver = 0.005;
        const float spawnChanceGold = 0.004;
        const float spawnChancePlatinum = 0.003;
        const float spawnChanceDiamonds = 0.001;
        
        /* Stores */
        const glm::vec2 storeSize(Constants::cellSize*3, Constants::cellSize*2);
        const glm::vec2 fuelStorePosition(cellSize * 4, -cellSize);
        const glm::vec2 refineryPosition(cellSize * 16, -cellSize);
        const glm::vec2 upgradeStorePosition(cellSize * 28, -cellSize);
        const int fuelPrice = 8;
        const int mineralPrices[] = {0, 0, 2, 4, 10, 25, 50, 100};
        const float tankCapacityModifierIncrease = 1.3f;
        const float healthCapacityModifierIncrease = 1.3f;
        const float drillSpeedModifierIncrease = 0.3f;
        const float priceIncrease = 2;
        const int baseFueltankPrice = 65;
        const int baseHullPrice = 80;
        const int baseDrillPrice = 100;
        
        /* Debug */
        const float cameraSpeed = 300;
        const glm::vec4 debugQuadColor(0, 155, 20, 0);
        const glm::vec4 debugNeighborQuadColor(155, 20, 20, 0);
        const glm::vec4 debugCircleColor(255, 0, 0, 0);
        const glm::vec4 debugLineColor(0, 0, 255, 0);
        const glm::vec4 debugPenetrationColor(140, 140, 0, 0);
        const int debugVertexCount = 8;
        static const char* debugFont = "data/fonts/VCR_OSD_MONO_1.001.ttf";
        const glm::vec2 fpsPanelPosition(initialWindowWidth - initialWindowWidth / 5, 20);
        
        /* Physics */
        const float baseImpulse = 60.0f;
        const float correctionPercent = 0.2f;
        const float correctionSlop = 0.01f;
        const glm::vec2 up = glm::vec2(0.0f, -1.0f);
        const glm::vec2 down = glm::vec2(0.0f, 1.0f);
        const glm::vec2 left = glm::vec2(-1.0f, 0.0f);
        const glm::vec2 right = glm::vec2(1.0f, 0.0f);
        
        /* UI */
        const glm::vec2 centerScreen(initialWindowWidth / 2.0f, initialWindowHeight / 2.0f);

        const glm::vec2 depthPanelPosition(20, 20);
        const glm::vec2 lowestDepthPanelPosition(20, 60);
        
        const glm::vec2 fuelPanelPosition(initialWindowWidth / 2 - 50, 20);
        const glm::vec2 moneyPanelPosition(initialWindowWidth / 2 + 50, 20);

        const glm::vec2 granitePanelPosition(20, initialWindowHeight - 100);
        const glm::vec2 ironPanelPosition(20, initialWindowHeight - 70);
        const glm::vec2 goldPanelPosition(20, initialWindowHeight - 40);

        const glm::vec2 drillPanelPosition(initialWindowWidth - initialWindowWidth / 5, initialWindowHeight - 100);
        const glm::vec2 hullPanelPosition(initialWindowWidth - initialWindowWidth / 5, initialWindowHeight - 70);
        const glm::vec2 gastankPanelPosition(initialWindowWidth - initialWindowWidth / 5, initialWindowHeight - 40);

        const SDL_Color textColor = {100, 255, 100, 255};
        const SDL_Color lowFuelTextColor = {255, 80, 60, 255};
        const int fontSize = 20;
        
        /* Clear colors */
        const glm::vec4 firstClearColor(0, 40, 130, 1);
        const glm::vec4 secondClearColor(30, 110, 60, 1);
        const glm::vec4 thirdClearColor(100, 60, 20, 1);
        const float firstColorCutoff = 1000.0f;
        const float secondColorCutoff = 2000.0f;
        
    } // namespace Constants
} // namespace Motherload
