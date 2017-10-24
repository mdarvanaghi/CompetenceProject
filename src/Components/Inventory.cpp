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

        this->maxFuel = 100.0f;
        this->maxHealth = 100.0f;
        this->fuel = 50.0f;
        this->health = 70.0f;
    }

    void Inventory::addMineral(MineralType mineral)
    {
        std::string mineralString;
        this->minerals[mineral]++;
        switch (mineral)
        {
            case (MineralType::Granite):
            {
                mineralString = "Granite: " + std::to_string(minerals[mineral]);
                Game::instance->granitePanel->setText(mineralString);
                break;
            }
            case (MineralType::Iron):
            {
                mineralString = "Iron: " + std::to_string(minerals[mineral]);
                Game::instance->ironPanel->setText(mineralString);
                break;
            }
            case (MineralType::Gold):
            {
                mineralString = "Gold: " + std::to_string(minerals[mineral]);
                Game::instance->goldPanel->setText(mineralString);
                break;
            }
        }
    }

    void Inventory::upgradeItem(UpgradeType type)
    {

    }

} // namespace Motherload
