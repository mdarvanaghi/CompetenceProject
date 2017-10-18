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
        this->minerals[mineral]++;
        std::string inventoryUiText = "Inventory:\n";
        for (int i = 0; i < MineralType::NUM_MINERALS; i++)
        {
            inventoryUiText += std::to_string((MineralType) i) + std::to_string(minerals[i]);
        }
        Game::instance->inventoryPanel->setText(inventoryUiText.c_str());
    }
} // namespace Motherload