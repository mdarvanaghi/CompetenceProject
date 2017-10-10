#pragma once

#include <string>
#include "Entities/PhysicalEntity.h"
#include "MineralType.h"

namespace Motherload
{
    class Block : public PhysicalEntity
    {
    public:
        MineralType mineralType;
        Block(MineralType mineralType);
    };
} // namespace Motherload
