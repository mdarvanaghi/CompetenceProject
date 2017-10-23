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
    private:
        void setTexture();

    public:
        MineralType mineralType;
        glm::vec2 coordinates;
        Block(glm::vec2 position, glm::vec2 size = glm::vec2(Constants::cellSize, Constants::cellSize));
        void initialize(MineralType mineralType, glm::vec2 coordinates);
    };
} // namespace Motherload    
