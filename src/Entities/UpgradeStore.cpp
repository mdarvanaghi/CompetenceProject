#include "Entities/UpgradeStore.h"

namespace Motherload
{
    UpgradeStore::UpgradeStore(glm::vec2 position, glm::vec2 size)
    {
        this->transform = new Transform(this, position, size);
        this->name = "Upgrade store";

        /* Physics */
        this->collider = new Physics::Collider(this);
        this->collider->isTrigger = true;
        this->isDynamic = false;
    }
    
    void UpgradeStore::initialize()
    {
        this->texture = ResourceManager::getTexture("data/textures/upgradestore.png");
        uiPanel = UISystem::addPanel(Constants::centerScreen, upgradeStrings, true);
        uiPanel->wrapAfterPixels = uiPanel->size.x;
        uiPanel->setBackgroundPanel(ResourceManager::getTexture("data/textures/uipanel.png"), 30.0f);
        uiPanel->setActive(false);
        playerInventory = Game::instance->player->inventory;
    }

    void UpgradeStore::activeUpdate()
    {
        if (InputSystem::getKeyDown(SDL_SCANCODE_T))
        {
            if (playerInventory->money >= fueltankPrice)
            {
                buyUpgrade(UpgradeType::Tank);
            }
        }
        
        if (InputSystem::getKeyDown(SDL_SCANCODE_U))
        {
            if (playerInventory->money >= hullPrice)
            {
                buyUpgrade(UpgradeType::Hull);
            }
        }
        
        if (InputSystem::getKeyDown(SDL_SCANCODE_I))
        {
            if (playerInventory->money >= drillPrice)
            {
                buyUpgrade(UpgradeType::Drill);
            }
        }
    }
    
    void UpgradeStore::buyUpgrade(UpgradeType upgrade)
    {
        switch (upgrade)
        {
            case (UpgradeType::Tank):
            {
                playerInventory->maxFuel *= Constants::tankCapacityModifierIncrease;
                playerInventory->fueltankLevel++;
                playerInventory->addMoney(-fueltankPrice);
                playerInventory->fuel = playerInventory->maxFuel;
                playerInventory->fueltankPanel->setText("Fuel tank level: " + std::to_string(playerInventory->fueltankLevel));
                break;
            }
            case (UpgradeType::Hull):
            {
                playerInventory->maxHealth *= Constants::healthCapacityModifierIncrease;
                playerInventory->hullLevel++;
                playerInventory->addMoney(-hullPrice);
                playerInventory->hullPanel->setText("Hull level: " + std::to_string(playerInventory->hullLevel));
                break;
            }
            case (UpgradeType::Drill):
            {
                playerInventory->drillModifier += Constants::drillSpeedModifierIncrease;
                playerInventory->drillLevel++;
                playerInventory->addMoney(-drillPrice);
                playerInventory->drillPanel->setText("Drill level: " + std::to_string(playerInventory->drillLevel));
                break;
            }
        }
        resetUi();
    }
    
    void UpgradeStore::resetUi()
    {
        updatePrices();
        upgradeStrings.clear();
        upgradeStrings.push_back
        (
            "Fuel tank upgrade: $" +
            std::to_string(fueltankPrice)
        );
        upgradeStrings.push_back("Press T to purchase");
        upgradeStrings.push_back("-----------------------");
        upgradeStrings.push_back
        (
            "Hull upgrade:      $" +
            std::to_string(hullPrice)
        );
        upgradeStrings.push_back("Press U to purchase");
        upgradeStrings.push_back("-----------------------");
        upgradeStrings.push_back
        (
            "Drill upgrade:     $" +
            std::to_string(drillPrice)
        );
        upgradeStrings.push_back("Press I to purchase");
        uiPanel->setText(upgradeStrings);
    }
    
    void UpgradeStore::updatePrices()
    {
        fueltankPrice = Constants::baseFueltankPrice + (Constants::baseFueltankPrice * playerInventory->fueltankLevel * Constants::priceIncrease);
        hullPrice = Constants::baseHullPrice + (Constants::baseHullPrice * playerInventory->hullLevel * Constants::priceIncrease);
        drillPrice = Constants::baseDrillPrice + (Constants::baseDrillPrice * playerInventory->drillLevel * Constants::priceIncrease);
    }
} // namespace Motherload
