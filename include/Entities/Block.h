#pragma once

#include <string>
#include "Entities/PhysicalEntity.h"
#include "MineralType.h"
#include "Systems/ResourceManager.h"

namespace Motherload
{
    class Block : public PhysicalEntity
    {
    public:
        MineralType mineralType;
        Block(MineralType mineraltype, glm::vec2 position);
        void initialize();
    };
} // namespace Motherload
