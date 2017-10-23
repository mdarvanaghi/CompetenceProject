#pragma once

namespace Motherload
{
    enum UpgradeType
    {
        Hull,
        Drill,
        Tank,
        NUM_UPGRADES
    };

    struct Upgrade
    {
    private:
        float modifierPerLevel;
    public:
        UpgradeType type;
        int level;
        float modifier;

        Upgrade(UpgradeType type, float modifierPerLevel);
        void upgrade();
    };
} // namespace Motherload