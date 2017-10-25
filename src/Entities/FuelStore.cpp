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
        this->tankFullString = "Tank is full.";
        this->texture = ResourceManager::getTexture("data/textures/fuelstore.png");
        uiPanel = UISystem::addPanel(Constants::centerScreen, buyString, true);
        uiPanel->setBackgroundPanel(ResourceManager::getTexture("data/textures/uipanel.png"), 30.0f);
        uiPanel->setActive(false);
        playerInventory = Game::instance->player->inventory;
    }

    void FuelStore::activeUpdate()
    {
        if (InputSystem::getKeyDown(SDL_SCANCODE_SPACE))
        {
            if
            (
                playerInventory->money >= fuelPrice && // Player has enough money
                playerInventory->fuel / playerInventory->maxFuel < 0.98f) // And tank is not nearly full
            {
                buyFuel();
            }
        }
    }

    void FuelStore::buyFuel()
    {
        playerInventory->fuel = playerInventory->maxFuel;
        playerInventory->addMoney(-Constants::fuelPrice);
        resetUi();
    }

    void FuelStore::resetUi()
    {
        if (playerInventory->fuel / playerInventory->maxFuel >= 0.98f)
        {
            uiPanel->setText(tankFullString);
        }
        else
        {
            uiPanel->setText(buyString);
        }
    }
}
