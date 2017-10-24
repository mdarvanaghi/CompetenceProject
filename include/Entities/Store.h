#pragma once
#include <string>
#include "Entities/PhysicsEntity.h"

namespace Motherload
{
    struct UIPanel;
    class Store : public Physics::PhysicsEntity
    {
    protected:
        bool active;
        UIPanel* uiPanel;

        virtual void updateUi() {}
    public:
        void update(float deltaTime);
        void isColliding(Physics::PhysicsEntity* other);
    };
} // namespace Motherload
