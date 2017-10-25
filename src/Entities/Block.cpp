#include "Entities/Block.h"

namespace Motherload
{
    Block::Block(glm::vec2 position, glm::vec2 coordinates, glm::vec2 size)
    {
        this->name = "Block";
        this->transform = new Transform(this, position, size);
        this->coordinates = coordinates;
        
        /* Physics */
        this->collider = new Physics::Collider(this);
        this->restitution = 1.0f;
        this->isDynamic = false;
        setMass(0.0f); // Static object with infinite mass
    }
    
    void Block::initialize()
    {
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
