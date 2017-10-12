#pragma once

#include <string>
#include "Entities/PhysicsEntity.h"
#include "MineralType.h"
#include "Systems/ResourceManager.h"
#include "Constants.h"

namespace Motherload
{
    class Block : public Physics::PhysicsEntity
    {
    public:
        MineralType mineralType;
        Block(glm::vec2 position, glm::vec2 size = glm::vec2(Constants::cellSize, Constants::cellSize));
        void initialize(MineralType mineralType);
        void setTexture();
    };
} // namespace Motherload    
