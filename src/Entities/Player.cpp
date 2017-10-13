#include "Entities/Player.h"

namespace Motherload
{
    Player::Player(glm::vec2 position)
    {
        this->transform = new Transform(this, position);
    }

    void Player::initialize()
    {
        this->name = "Player";
        this->texture = ResourceManager::getTexture("data/textures/tank.png");

        /* Physics */
        this->collider = new Collider(this);
        this->accelerationX = Constants::playerAccelerationX;
        this->decelerationX = Constants::playerDecelerationX;
        this->accelerationY = Constants::playerAccelerationY;
        this->maxSpeedX = Constants::playerMaxSpeedX;
        this->maxSpeedY = Constants::playerTerminalVelocity;
        this->velocity = glm::vec2(0);
        this->isDynamic = true;
    }

    void Player::update(float deltaTime)
    {
        
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

    void Player::handleInput(float deltaTime)
    {
        if (InputSystem::getKey(SDL_SCANCODE_UP))
        {
            velocity.y -= accelerationY * deltaTime;
        }
        if (InputSystem::getKey(SDL_SCANCODE_LEFT))
        {
            velocity.x -= accelerationX * deltaTime;
            accelerating = true;
        }
        if (InputSystem::getKey(SDL_SCANCODE_RIGHT))
        {
            velocity.x += accelerationY * deltaTime;
            accelerating = true;
        }
    }

    void Player::decelerate()
    {
        if (velocity.x < 0) velocity.x += decelerationX;
        if (velocity.x > 0) velocity.x -= decelerationX;
        
        // Make sure player stops completely
        if (velocity.x > 0 && velocity.x < decelerationX) velocity.x = 0;
        if (velocity.x < 0 && velocity.x > -decelerationX) velocity.x = 0;
    }

} // namespace Motherload