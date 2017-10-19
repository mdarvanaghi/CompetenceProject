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
    }

    void Inventory::addMineral(MineralType mineral)
    {
        std::string mineralString;
        this->minerals[mineral]++;
        switch (mineral)
        {
            case (MineralType::Granite):
            {
                mineralString = "Granite " + std::to_string(minerals[mineral]);
                Game::instance->granitePanel->setText(mineralString.c_str());
                break;
            }
            case (MineralType::Iron):
            {
                mineralString = "Iron " + std::to_string(minerals[mineral]);
                Game::instance->ironPanel->setText(mineralString.c_str());
                break;
            }
            case (MineralType::Gold):
            {
                mineralString = "Gold " + std::to_string(minerals[mineral]);
                Game::instance->goldPanel->setText(mineralString.c_str());
                break;
            }
        }
    }
} // namespace Motherload