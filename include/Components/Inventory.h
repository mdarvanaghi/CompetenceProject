#pragma once

#include <vector>
#include <string>
#include <sstream>
#include "MineralType.h"
#include "Components/Upgrade.h"
#include "Entities/Entity.h"
#include "Game.h"
#include "Systems/UI/UIPanel.h"

namespace Motherload
{
    struct UIPanel;
    class Inventory : public Component
    {
    private:
        void updateMineral(MineralType mineral);
        UIPanel* moneyPanel;
        UIPanel* granitePanel;
        UIPanel* ironPanel;
        UIPanel* goldPanel;
        UIPanel* drillPanel;
        UIPanel* hullPanel;
        UIPanel* gastankPanel;

    public:
        // Variables
        std::vector<int> minerals;
        std::vector<Upgrade> upgrades;
        int money = Constants::startMoney;
        float fuel;
        float maxFuel;
        float health;
        float maxHealth;
        bool hasMinerals;

        // Methods
        Inventory(Entity* entity);
        void initializeUi();
        void addMineral(MineralType mineral);
        void resetMinerals();
        void addMoney(int amount);
        void upgradeItem(UpgradeType type);
    };
} // namespace Motherload
