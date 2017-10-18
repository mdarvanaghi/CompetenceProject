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
    }
} // namespace Motherload