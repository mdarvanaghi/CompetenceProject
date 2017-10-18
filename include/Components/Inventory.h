#pragma once

#include <vector>
#include <string>
#include "MineralType.h"
#include "Components/Upgrade.h"
#include "Entities/Entity.h"
#include "Game.h"

namespace Motherload
{
    class Inventory : public Component
    {
    public:
        // Variables
        std::vector<int> minerals;
        std::vector<Upgrade> upgrades;

        // Methods
        Inventory(Entity* entity);
        void addMineral(MineralType mineral);
    };
} // namespace Motherload