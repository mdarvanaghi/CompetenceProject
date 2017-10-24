#include "Entities/Refinery.h"

namespace Motherload
{
    Refinery::Refinery(glm::vec2 position, glm::vec2 size)
    {
        this->transform = new Transform(this, position, size);
        this->name = "Refinery";

        /* Physics */
        this->collider = new Physics::Collider(this);
        this->collider->isTrigger = true;
        this->isDynamic = false;
    }

    void Refinery::activeUpdate()
    {
        if (InputSystem::getKeyDown(SDL_SCANCODE_SPACE))
        {
            sellMinerals();
        }
    }

    void Refinery::initialize()
    {

        this->texture = ResourceManager::getTexture("data/textures/refinery.png");
        uiPanel = UISystem::addPanel(Constants::centerScreen, buyStrings, true);
        uiPanel->wrapAfterPixels = uiPanel->size.x;
        uiPanel->setBackgroundPanel(ResourceManager::getTexture("data/textures/uipanel.png"), 30.0f);
        uiPanel->setActive(false);
    }

    void Refinery::resetUi()
    {
        buyStrings.clear();
        totalMoney = 0;
        for (int i = 0; i < MineralType::NUM_MINERALS; i++)
        {
            totalMoney += Game::instance->player->inventory->minerals[i] * Constants::mineralPrices[i];
        }

        this->buyStrings.push_back
        (
            "Granite: " +
            std::to_string(Game::instance->player->inventory->minerals[MineralType::Granite]) +
            " x $" + std::to_string(Constants::mineralPrices[MineralType::Granite])
        );
        this->buyStrings.push_back
        (
            "Iron: " +
            std::to_string(Game::instance->player->inventory->minerals[MineralType::Iron]) +
                " x $" + std::to_string(Constants::mineralPrices[MineralType::Iron])
        );
        this->buyStrings.push_back
        (
            "Gold: " +
            std::to_string(Game::instance->player->inventory->minerals[MineralType::Gold]) +
                " x $" + std::to_string(Constants::mineralPrices[MineralType::Gold])
        );
        this->buyStrings.push_back("Total: $" + std::to_string(totalMoney));
        this->buyStrings.push_back("----------------------------");
        this->buyStrings.push_back("Press SPACE to sell minerals.");
        uiPanel->setText(buyStrings);
    }

    void Refinery::sellMinerals()
    {
        for (int& mineral: Game::instance->player->inventory->minerals)
        {
            mineral = 0;
        }
        Game::instance->player->inventory->addMoney(totalMoney);
        Game::instance->player->inventory->resetMinerals();
        resetUi();
    }
} // namespace Motherload
