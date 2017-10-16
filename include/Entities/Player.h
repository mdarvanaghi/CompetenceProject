#pragma once

#include "glm/glm.hpp"
#include "Entities/PhysicsEntity.h"
#include "Systems/InputSystem.h"
#include "Systems/ResourceManager.h"
#include "Constants.h"
#include "Entities/Block.h"
#include "Extensions.h"

namespace Motherload
{
    class Block;
    class Player : public Physics::PhysicsEntity
    {
    private:
        bool accelerating;
        bool startDrilling;
        bool isDrilling;
        bool collidingThisFrame;

        float accelerationX, decelerationX;
        float accelerationY;

        PhysicsEntity* currentBlockBelow;
        glm::vec2 drillOrigin;

        float timeDrilled;

        void handleInput(float deltaTime);
        void decelerate();
        void setDrillingMode(bool value);
        void drill(float deltaTime);
        void collectMineral();

    public:
        Player(glm::vec2 position);
        void update(float deltaTime);
        void initialize();
        void physicsUpdate(float deltaTime);
        void isColliding(PhysicsEntity* block);
    };
} // namespace Motherload
