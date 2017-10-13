#include "Entities/Player.h"

namespace Motherload
{
    Player::Player(glm::vec2 position)
    {
        this->transform = new Transform(this, position);
    }

    void Player::update(float deltaTime)
    {

    }
} // namespace Motherload