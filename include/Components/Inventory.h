#pragma once

#include <vector>
#include <string>
#include <sstream>
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
        int money = Constants::startMoney;
        float fuel;
        float maxFuel;
        float health;
        float maxHealth;

        // Methods
        Inventory(Entity* entity);
        void addMineral(MineralType mineral);
        void upgradeItem(UpgradeType type);
    };
} // namespace Motherload
