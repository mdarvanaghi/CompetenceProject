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

    void Refinery::updateUi()
    {
        if (InputSystem::getKeyDown(SDL_SCANCODE_SPACE))
        {
            Game::instance->player->inventory->money += 5000;
        }
    }

    void Refinery::initialize()
    {
        this->granitePrice = Constants::granitePrice;
        this->ironPrice = Constants::ironPrice;
        this->goldPrice = Constants::goldPrice;

        this->buyStrings.push_back("Hello");
        this->buyStrings.push_back("Is there anybody in there?");
        this->buyStrings.push_back("Just nod if you can hear me");

        this->texture = ResourceManager::getTexture("data/textures/refinery.png");
        uiPanel = UISystem::addPanel(Constants::centerScreen, buyStrings, true);
        uiPanel->wrapAfterPixels = uiPanel->size.x;
        uiPanel->setBackgroundPanel(ResourceManager::getTexture("data/textures/uipanel.png"), 30.0f);
        uiPanel->setActive(false);
    }
} // namespace Motherload
