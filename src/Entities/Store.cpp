#include "Entities/Store.h"
#include "Systems/UI/UIPanel.h"

namespace Motherload
{
    void Store::update(float deltaTime)
    {
        if (active)
        {
            activeUpdate();
            if (!activeLastFrame)
            {
                resetUi();
            }
        }
        uiPanel->setActive(active);
        activeLastFrame = active;
        active = false;
    }

    void Store::isColliding(Physics::PhysicsEntity* other)
    {
        active = true;
    }
} // namespace Motherload
