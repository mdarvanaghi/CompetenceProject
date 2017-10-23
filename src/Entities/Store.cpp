#include "Entities/Store.h"

namespace Motherload
{
    Store::Store(glm::vec2 position, glm::vec2 size)
    {
        this->transform = new Transform(this, position, size);
    }
    
    void Store::initialize(StoreType type, std::string texture)
    {
        this->name = "Store";
        this->texture = ResourceManager::getTexture(texture);
        uiPanel = UISystem::addPanel(Constants::centerScreen, "STORE IS OPEN YES", true);
        uiPanel->setBackgroundPanel(ResourceManager::getTexture("data/textures/uipanel.png"), 30.0f);

        /* Physics */
        this->collider = new Physics::Collider(this);
        this->collider->isTrigger = true;
        this->isDynamic = false;
    }

    void Store::update(float deltaTime)
    {
        uiPanel->setActive(active);
        active = false;
    }

    void Store::isColliding(Physics::PhysicsEntity* other)
    {
        active = true;
    }
} // namespace Motherload