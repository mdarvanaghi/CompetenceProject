#include "Entities/FuelStore.h"

namespace Motherload
{
    FuelStore::FuelStore(glm::vec2 position, glm::vec2 size)
    {
        this->transform = new Transform(this, position, size);
        this->name = "Fuel store";

        /* Physics */
        this->collider = new Physics::Collider(this);
        this->collider->isTrigger = true;
        this->isDynamic = false;
    }

    void FuelStore::initialize()
    {
        this->fuelPrice = Constants::fuelPrice;
        this->buyString = "Press SPACE to fill tank ($" + std::to_string(fuelPrice) + ").";
        this->texture = ResourceManager::getTexture("data/textures/fuelstore.png");
        uiPanel = UISystem::addPanel(Constants::centerScreen, buyString, true);
        uiPanel->setBackgroundPanel(ResourceManager::getTexture("data/textures/uipanel.png"), 30.0f);
        uiPanel->setActive(false);
    }

    void FuelStore::updateUi()
    {
        if (InputSystem::getKeyDown(SDL_SCANCODE_SPACE))
        {
            Game::instance->player->inventory->fuel = Game::instance->player->inventory->maxFuel;
            Game::instance->player->inventory->money -= 20;
        }
    }
}
