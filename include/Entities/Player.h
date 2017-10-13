#pragma once

#include "glm/glm/glm.hpp"
#include "Entities/PhysicsEntity.h"
#include "Systems/InputSystem.h"
#include "Systems/ResourceManager.h"
#include "Constants.h"

namespace Motherload
{
    class Player : public Physics::PhysicsEntity
    {
    private:
        bool accelerating;
        float accelerationX, decelerationX;
        float accelerationY;
        
        void handleInput(float deltaTime);
        void decelerate();

    public:
        Player(glm::vec2 position);
        void update(float deltaTime);
        void initialize();
        void physicsUpdate(float deltaTime);
    };
} // namespace Motherload
