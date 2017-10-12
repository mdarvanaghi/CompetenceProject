#pragma once

#include <string>
#include "Entities/PhysicalEntity.h"
#include "MineralType.h"
#include "Systems/ResourceManager.h"
#include "Constants.h"

namespace Motherload
{
    class Block : public PhysicalEntity
    {
    public:
        MineralType mineralType;
        Block(glm::vec2 position, glm::vec2 scale = glm::vec2(Constants::cellSize, Constants::cellSize));
        void initialize(MineralType mineralType);
        void setTexture();
    };
} // namespace Motherload    
