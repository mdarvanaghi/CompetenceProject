#include "Entities/Block.h"

namespace Motherload
{
    Block::Block(glm::vec2 position, glm::vec2 size)
    {
        this->transform = new Transform(this, position, size);
    }

    void Block::initialize(MineralType mineralType)
    {
        this->name = "Block";
        this->mineralType = mineralType;

        /* Physics */
        this->collider = new Collider(this);
        this->isDynamic = false;
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