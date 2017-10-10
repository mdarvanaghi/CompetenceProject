#include "Entities/Block.h"

namespace Motherload
{
    Block::Block(MineralType mineraltype, glm::vec2 position)
    {
        this->position = position;
        this->mineralType = mineralType;
    }

    void Block::initialize()
    {
        switch (mineralType)
        {
            case (MineralType::Dirt):
            {
                texture = ResourceManager::getTexture("dirt.png");
                break;
            }
            case (MineralType::Granite):
            {
                texture = ResourceManager::getTexture("granite.png");
                break;
            }
            case (MineralType::Iron):
            {
                texture = ResourceManager::getTexture("iron.png");
                break;
            }
            case (MineralType::Gold):
            {
                texture = ResourceManager::getTexture("gold.png");
                break;
            }
        }
    }
}