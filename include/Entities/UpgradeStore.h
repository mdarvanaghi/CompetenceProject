#pragma once
#include <string>
#include "SDL.h"
#include "Entities/Store.h"
#include "Systems/UI/UIPanel.h"
#include "Components/Upgrade.h"

namespace Motherload
{
    class UpgradeStore : public Store
    {
    private:
        int drillPrice;
        int hullPrice;
        int fueltankPrice;

        std::vector<std::string> upgradeStrings;

        void buyUpgrade(UpgradeType upgrade);

        void activeUpdate();
        void resetUi();
        void updatePrices();
    public:
        UpgradeStore(glm::vec2 position, glm::vec2 size);
        void initialize();
    };
} // namespace Motherload
