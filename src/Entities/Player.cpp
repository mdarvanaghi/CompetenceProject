#include "Entities/PhysicalEntity.h"
#include "Entities/Player.h"

namespace Motherload
{
    Player::Player(glm::vec2 position)
    {
        this->transform = new Transform(position);
    }
} // namespace Motherload