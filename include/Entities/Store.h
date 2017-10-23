#pragma once
#include <string>
#include "Entities/PhysicsEntity.h"
#include "Systems/ResourceManager.h"
#include "Systems/UI/UIPanel.h"

namespace Motherload
{
    class UIPanel;

    enum StoreType
    {
        UpgradeStore,
        Refinery,
        FuelStore
    };

    class Store : public Physics::PhysicsEntity
    {
    private:
        StoreType type;
        bool active;
        UIPanel* uiPanel;

    public:
        Store(glm::vec2 position, glm::vec2 size);
        void initialize(StoreType type, std::string texture);
        void update(float deltaTime);
        void isColliding(Physics::PhysicsEntity* other);
    };
} // namespace Motherload