#include "Entities/Player.h"

namespace Motherload
{
    Player::Player(glm::vec2 position)
    {
        this->transform = new Transform(this, position);
        this->inventory = new Inventory(this);
    }

    void Player::initialize()
    {
        this->name = "Player";
        this->texture = ResourceManager::getTexture("data/textures/tank.png");

        /* Physics */
        this->collider = new Physics::Collider(this);
        this->restitution = 0.2f;
        this->accelerationX = Constants::playerAccelerationX;
        this->decelerationX = Constants::playerDecelerationX;
        this->accelerationY = Constants::playerAccelerationY;
        this->maxSpeedX = Constants::playerMaxSpeedX;
        this->maxSpeedY = Constants::playerTerminalVelocity;
        this->isDynamic = true;
    }

    void Player::update(float deltaTime)
    {
        if (isDrilling)
        {
            drill(deltaTime);
            return;
        }

        if (!collidingThisFrame)
        {
            currentBlockBelow = nullptr;
            startDrilling = false;
            return;
        }
        collidingThisFrame = false;

        if (startDrilling)
        {
            setDrillingMode(true);
            startDrilling = false;
        }
    }

    void Player::physicsUpdate(float deltaTime)
    {
        accelerating = false;
        handleInput(deltaTime);
        if (!accelerating)
        {
            decelerate();
        }
    }

    void Player::isColliding(PhysicsEntity* block)
    {
        collidingThisFrame = true;
        if (block->transform->positionWorldSpace.y > transform->positionWorldSpace.y)
        {
            if (currentBlockBelow == nullptr)
            {
                currentBlockBelow = (Block*) block;
            }
            else if 
            (glm::abs(block->transform->positionWorldSpace.x - transform->positionWorldSpace.x)
                < glm::abs(currentBlockBelow->transform->positionWorldSpace.x - transform->positionWorldSpace.x)) 
            {
                currentBlockBelow = (Block*) block;
            }
        }
    }

    void Player::handleInput(float deltaTime)
    {
        if (InputSystem::getKey(SDL_SCANCODE_UP))
        {
            addForce(Constants::up * accelerationY * deltaTime);
        }
        if (InputSystem::getKey(SDL_SCANCODE_DOWN))
        {
            startDrilling = true;
        }
        if (InputSystem::getKey(SDL_SCANCODE_LEFT))
        {
            addForce(Constants::left * accelerationX * deltaTime);
            accelerating = true;
        }
        if (InputSystem::getKey(SDL_SCANCODE_RIGHT))
        {
            addForce(Constants::right * accelerationY * deltaTime);
            accelerating = true;
        }
    }

    void Player::decelerate()
    {
        if (velocity.x < 0.0f) velocity.x += decelerationX;
        if (velocity.x > 0.0f) velocity.x -= decelerationX;
        
        // Make sure player stops completely
        if (velocity.x > 0.0f && velocity.x < decelerationX) velocity.x = 0.0f;
        if (velocity.x < 0.0f && velocity.x > -decelerationX) velocity.x = 0.0f;
    }

    void Player::setDrillingMode(bool value)
    {
        isDrilling = value;
        isDynamic = !value;
        if (isDrilling)
        {
            drillOrigin = transform->positionWorldSpace;
            timeDrilled = 0.0f;
        }
        else 
        {
            currentBlockBelow = nullptr;
        }
    }

    void Player::drill(float deltaTime)
    {
        timeDrilled += deltaTime;
        float progress = timeDrilled / Constants::drillTime;
        transform->positionWorldSpace = Extensions::Vector2::lerp(drillOrigin, currentBlockBelow->transform->positionWorldSpace, progress);
        if (progress >= 1.0f)
        {
            collectMineral();
            setDrillingMode(false);
        }
    }

    void Player::collectMineral()
    {
        inventory->addMineral(currentBlockBelow->mineralType);
        Game::instance->destroyEntity(currentBlockBelow);
    }

} // namespace Motherload