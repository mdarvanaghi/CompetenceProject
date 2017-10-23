#include "Entities/Block.h"

namespace Motherload
{
    Block::Block(glm::vec2 position, glm::vec2 size)
    {
        this->transform = new Transform(this, position, size);
    }

    void Block::initialize(MineralType mineralType, glm::vec2 coordinates)
    {
        this->name = "Block";
        this->mineralType = mineralType;
        this->coordinates = coordinates;

        /* Physics */
        this->collider = new Physics::Collider(this);
        this->restitution = 1.0f;
        this->isDynamic = false;
        setMass(0.0f); // Static object with infinite mass
        setTexture();
    }

    void Block::setTexture()
    {
        switch (this->mineralType)
        {
            case (MineralType::Dirt):
            {
                this->texture = ResourceManager::getTexture("data/textures/dirt.png");
                break;
            }
            case (MineralType::Granite):
            {
                this->texture = ResourceManager::getTexture("data/textures/granite.png");
                break;
            }
            case (MineralType::Iron):
            {
                this->texture = ResourceManager::getTexture("data/textures/iron.png");
                break;
            }
            case (MineralType::Gold):
            {
                this->texture = ResourceManager::getTexture("data/textures/gold.png");
                break;
            }
        }
    }
} // namespace Motherload