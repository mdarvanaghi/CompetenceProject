#include "Entities/Store.h"
#include "Systems/UI/UIPanel.h"

namespace Motherload
{
    void Store::update(float deltaTime)
    {
        uiPanel->setActive(active);
        if (active)
        {
            updateUi();
        }
        active = false;
    }

    void Store::isColliding(Physics::PhysicsEntity* other)
    {
        active = true;
    }
} // namespace Motherload
