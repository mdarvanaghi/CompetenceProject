#include "Entities/Player.h"

namespace Motherload
{
    Player::Player(glm::vec2 position)
    {
        this->transform = new Transform(this, position, glm::vec2(36, 36));
        this->inventory = new Inventory(this);
        this->isDrilling = false;
        this->isGrounded = false;
        this->accelerating = false;
        this->lifting = false;
        this->startDrilling = false;
        this->collidingWithBlockDrilling = false;
    }

    void Player::initialize()
    {
        this->name = "Player";
        this->texture = ResourceManager::getTexture("data/textures/tank.png");
        this->inventory->initializeUi();

        /* Physics */
        this->collider = new Physics::Collider(this);
        this->restitution = 0.2f;
        this->accelerationX = Constants::playerAccelerationX;
        this->decelerationX = Constants::playerDecelerationX;
        this->accelerationY = Constants::playerAccelerationY;
        this->maxSpeedX = Constants::playerMaxSpeedX;
        this->maxSpeedY = Constants::playerTerminalVelocity;
        this->isDynamic = true;
        
        /* UI */
        depthPanel = UISystem::addPanel(Constants::depthPanelPosition, "Depth: 0", false);
        lowestDepthPanel = UISystem::addPanel(Constants::lowestDepthPanelPosition, "Lowest depth: 0", false);
    }

    void Player::physicsUpdate(float deltaTime)
    {
        neighbors = getNeighborBlocks();
        if (neighbors.size() > 0)
        {
            currentBlockBelow = neighbors[2][1];
            if (transform->positionWorldSpace.y > 0)
            {
                currentBlockLeft = neighbors[1][0];
                currentBlockRight = neighbors[1][2];
            }
            else
            {
                currentBlockLeft = nullptr;
                currentBlockRight = nullptr;
            }
        }

        handleInput(deltaTime);
        if (!accelerating)
        {
            decelerate();
        }
    }

    void Player::update(float deltaTime)
    {
        if (isDrilling)
        {
            drill(deltaTime);
            return;
        }

        if (!isGrounded)
        {
            currentBlockBelow = nullptr;
            currentBlockLeft = nullptr;
            currentBlockRight = nullptr;
            blockCurrentlyDrilling = nullptr;
            startDrilling = false;
            return;
        }
        isGrounded = false;
        if (!collidingWithBlockDrilling)
        {
            return;
        }
        collidingWithBlockDrilling = false;
        checkDrillRequest();
    }

    void Player::checkDrillRequest()
    {
        if (startDrilling)
        {
            requestDrillingMode(true);
        }
        startDrilling = false;
    }

    void Player::isColliding(PhysicsEntity* block)
    {
        if ((PhysicsEntity*) currentBlockBelow == block)
        {
            isGrounded = true;
        }
        if ((PhysicsEntity*) blockCurrentlyDrilling == block)
        {
            collidingWithBlockDrilling = true;
        }
    }

    void Player::handleInput(float deltaTime)
    {
        if (InputSystem::getKey(SDL_SCANCODE_UP))
        {
            lifting = true;
            addForce(Constants::up * accelerationY * deltaTime);
        }
        if (InputSystem::getKey(SDL_SCANCODE_LEFT))
        {
            addForce(Constants::left * accelerationX * deltaTime);
            accelerating = true;
            blockCurrentlyDrilling = currentBlockLeft;
            startDrilling = true;
        }
        if (InputSystem::getKey(SDL_SCANCODE_RIGHT))
        {
            addForce(Constants::right * accelerationY * deltaTime);
            accelerating = true;
            blockCurrentlyDrilling = currentBlockRight;
            startDrilling = true;
        }
        if (InputSystem::getKey(SDL_SCANCODE_DOWN))
        {
            blockCurrentlyDrilling = currentBlockBelow;
            startDrilling = true;
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

    void Player::requestDrillingMode(bool value)
    {

        isDrilling = value;
        isDynamic = !value;
        velocity = glm::vec2(0);

        if (isDrilling)
        {
            if (blockCurrentlyDrilling == nullptr)
            {
                return;
            }
            drillOrigin = transform->positionWorldSpace;
            timeDrilled = 0.0f;
        }
        else
        {
            blockCurrentlyDrilling = nullptr;
        }
    }

    void Player::drill(float deltaTime)
    {
        if (blockCurrentlyDrilling == nullptr)
        {
            requestDrillingMode(false);
            return;
        }
        timeDrilled += deltaTime;
        float progress = timeDrilled / Constants::baseDrillTime * inventory->drillModifier;
        transform->positionWorldSpace = Extensions::Vector2::lerp(drillOrigin, blockCurrentlyDrilling->transform->positionWorldSpace, progress);
        if (progress >= 1.0f)
        {
            collectMineral();
            requestDrillingMode(false);
        }
    }

    void Player::collectMineral()
    {
        inventory->addMineral(blockCurrentlyDrilling->mineralType);
        Game::instance->destroyBlock(blockCurrentlyDrilling);
    }

    std::vector<std::vector<Block*>> Player::getNeighborBlocks(int range)
    {
        int span = range * 2 + 1;
        glm::vec2 coordinates = transform->getPositionCoordinates();
        int depth = Game::instance->blocks.size();
        std::vector<std::vector<Block*>> neighbors = std::vector<std::vector<Block*>>(span);
        if (depth <= 0)
        {
            return neighbors;
        }
        int width = Game::instance->blocks[0].size();

        for (int i = 0; i < span; i++)
        {
            neighbors.at(i) = std::vector<Block*>(span);
            for (int j = 0; j < span; j++)
            {
                int worldCoordinateY = coordinates.y + (i - range);
                int worldCoordinateX = coordinates.x + (j - range);

                if
                (
                    (worldCoordinateY >= 0 && worldCoordinateY < depth) // Depth not out of range
                    && (worldCoordinateX >= 0 && worldCoordinateX < width) // Width not out of range
                    && (worldCoordinateY != coordinates.y && worldCoordinateX != coordinates.x) // Is not player
                )
                {
                    neighbors[i][j] = Game::instance->blocks[worldCoordinateY][worldCoordinateX];
                }
                else
                {
                    neighbors[i][j] = nullptr;
                }
            }
        }
        return neighbors;
    }
    
    void Player::lateUpdate(float deltaTime)
    {
        updateDepthMeters();
        spendFuel(deltaTime);
        accelerating = false;
        lifting = false;
    }
    
    void Player::updateDepthMeters()
    {
        int currentDepth = int (transform->positionWorldSpace.y);
        std::string depthString = "Depth: " + std::to_string(currentDepth);
        depthPanel->setText(depthString);

        if (currentDepth > lowestDepth)
        {
            lowestDepth = currentDepth;
            std::string lowestDepthString = "Lowest depth: " + std::to_string(lowestDepth);
            lowestDepthPanel->setText(lowestDepthString);
        }
    }
    
    void Player::spendFuel(float deltaTime)
    {
        if (isDrilling)
        {
            inventory->spendFuel(deltaTime * Constants::drillingFuelRate);
        }
        else if (accelerating || lifting)
        {
            inventory->spendFuel(deltaTime * Constants::acceleratingFuelRate);
        }
        else
        {
            inventory->spendFuel(deltaTime * Constants::idleFuelRate);
        }
    }
    
} // namespace Motherload
