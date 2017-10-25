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
        UIPanel* fuelPanel;
        
        UIPanel* granitePanel;
        UIPanel* ironPanel;
        UIPanel* goldPanel;

        void checkFuel();
    public:
        // Variables
        std::vector<int> minerals;
        std::vector<Upgrade> upgrades;
        int money = Constants::startMoney;
        float fuel;
        float fuelPercentage;
        float health;
        bool hasMinerals;
        
        UIPanel* drillPanel;
        UIPanel* hullPanel;
        UIPanel* fueltankPanel;
        
        // Item attributes
        float drillModifier;
        float maxFuel;
        float maxHealth;
        int drillLevel;
        int fueltankLevel;
        int hullLevel;        

        // Methods
        Inventory(Entity* entity);
        void initializeUi();
        void addMineral(MineralType mineral);
        void resetMinerals();
        void addMoney(int amount);
        void spendFuel(float deltaTime);
    };
} // namespace Motherload
