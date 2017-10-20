#pragma once

namespace Motherload
{
    enum UpgradeType
    {
        Hull,
        Drill,
        Tank
    };

    struct Upgrade
    {
    public:
        UpgradeType type;
        int level;
        float modifier;
    };
} // namespace Motherload