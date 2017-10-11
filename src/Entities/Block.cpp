#include "Entities/Block.h"

namespace Motherload
{
    Block::Block(glm::vec2 position, glm::vec2 scale)
    {
        this->transform = new Transform(position, scale);
    }

    void Block::initialize(MineralType mineralType)
    {
        this->mineralType = mineralType;
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
}