#include "Components/Upgrade.h"

namespace Motherload
{
    Upgrade::Upgrade(UpgradeType type, float modifierPerLevel)
    {
        this->type = type;
        this->modifierPerLevel = modifierPerLevel;
        this->level = 0;
        this->modifier = 1.0f;
    }

    void Upgrade::upgrade()
    {
        level++;
        modifier += modifierPerLevel;
    }
}