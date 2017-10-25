#include "Components/Inventory.h"

namespace Motherload
{
    Inventory::Inventory(Entity* entity)
    {
        this->entity = entity;
        this->minerals = std::vector<int>();
        for (int i = 0; i < MineralType::NUM_MINERALS; i++)
        {
            minerals.push_back(0);
        }
        
        this->upgrades = std::vector<Upgrade>();
        for (int i = 0; i < UpgradeType::NUM_UPGRADES; i++)
        {
            upgrades.push_back(Upgrade((UpgradeType) i, 0.3f));
        }
        this->money = Constants::startMoney;
        this->drillModifier = 0.5f;
        this->maxFuel = 100.0f;
        this->maxHealth = 100.0f;
        this->fuel = 50.0f;
        this->health = 70.0f;
        this->drillLevel = 0;
        this->hullLevel = 0;
        this->fueltankLevel = 0;
        this->hasMinerals = false;
    }

    void Inventory::initializeUi()
    {
        moneyPanel = UISystem::addPanel(Constants::moneyPanelPosition, "$20", true);
        fuelPanel = UISystem::addPanel(Constants::fuelPanelPosition, "50%", true);
        granitePanel = UISystem::addPanel(Constants::granitePanelPosition, "Granite: 0", false);
        ironPanel = UISystem::addPanel(Constants::ironPanelPosition, "Iron: 0", false);
        goldPanel = UISystem::addPanel(Constants::goldPanelPosition, "Gold: 0", false);
        drillPanel = UISystem::addPanel(Constants::drillPanelPosition, "Drill level: 0", false);
        hullPanel = UISystem::addPanel(Constants::hullPanelPosition, "Hull level: 0", false);
        fueltankPanel = UISystem::addPanel(Constants::gastankPanelPosition, "Gas tank level: 0", false);
    }

    void Inventory::addMineral(MineralType mineral)
    {
        this->minerals[mineral]++;
        updateMineral(mineral);
        hasMinerals = true;
    }

    void Inventory::updateMineral(MineralType mineral)
    {
        std::string mineralString;
        switch (mineral)
        {
            case (MineralType::Granite):
            {
                mineralString = "Granite: " + std::to_string(minerals[mineral]);
                granitePanel->setText(mineralString);
                break;
            }
            case (MineralType::Iron):
            {
                mineralString = "Iron: " + std::to_string(minerals[mineral]);
                ironPanel->setText(mineralString);
                break;
            }
            case (MineralType::Gold):
            {
                mineralString = "Gold: " + std::to_string(minerals[mineral]);
                goldPanel->setText(mineralString);
                break;
            }
        }
    }

    void Inventory::resetMinerals()
    {
        for (int i = 0; i < MineralType::NUM_MINERALS; i++)
        {
            updateMineral((MineralType) i);
        }
        hasMinerals = false;
    }

    void Inventory::addMoney(int amount)
    {
        money += amount;
        moneyPanel->setText("$" + std::to_string(money));
    }
    
    void Inventory::spendFuel(float amount)
    {
        fuel -= amount;
        fuelPercentage = (fuel / maxFuel) * 100;
        checkFuel();
    }

    void Inventory::checkFuel()
    {
        if (fuelPercentage < 25)
        {
            fuelPanel->setText(std::to_string((int) fuelPercentage) + "%", Constants::lowFuelTextColor);
            return;
        }
        fuelPanel->setText(std::to_string((int) fuelPercentage) + "%");
    }

} // namespace Motherload
