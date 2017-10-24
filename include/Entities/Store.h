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
        bool activeLastFrame = false;
        UIPanel* uiPanel;

        virtual void activeUpdate() {}
        virtual void resetUi() {}
    public:
        void update(float deltaTime);
        void isColliding(Physics::PhysicsEntity* other);
    };
} // namespace Motherload
