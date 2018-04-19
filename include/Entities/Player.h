#pragma once

#include "glm/glm.hpp"
#include "Entities/PhysicsEntity.h"
#include "Systems/InputSystem.h"
#include "Systems/ResourceManager.h"
#include "Constants.h"
#include "Entities/Block.h"
#include "Extensions.h"
#include "Components/Inventory.h"

namespace Motherload
{
    class Block;
    class Inventory;
    
    class Player : public Physics::PhysicsEntity
    {
    private:
        bool accelerating;
        bool lifting;
        bool startDrilling;
        bool isDrilling;
        bool isGrounded;
        bool collidingWithBlockDrilling;

        float accelerationX, decelerationX;
        float accelerationY;
        
        Block* currentBlockBelow;
        Block* currentBlockLeft;
        Block* currentBlockRight;
        Block* blockCurrentlyDrilling;
        glm::vec2 drillOrigin;
        
        float timeDrilled;
        
        void handleInput(float deltaTime);
        void decelerate();
        void checkDrillRequest();
        void requestDrillingMode(bool value);
        void drill(float deltaTime);
        void collectMineral();
        void updateDepthMeters();
        void spendFuel(float deltaTime);
        void checkBounds();
        void takeDamage(float amount);
        
        UIPanel* depthPanel;
        UIPanel* lowestDepthPanel;
        
    public:
        std::vector<std::vector<Block*>> neighbors;
        Inventory* inventory;
        int lowestDepth = 0;
        
        Player(glm::vec2 position);
        void initialize();
        void update(float deltaTime);
        void lateUpdate(float deltaTime);
        void physicsUpdate(float deltaTime);
        void isColliding(PhysicsEntity* other);
        std::vector<std::vector<Block*>> getNeighborBlocks(int range = 1);
    };
} // namespace Motherload
