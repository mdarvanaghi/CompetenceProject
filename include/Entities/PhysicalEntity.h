#pragma once

#include "SDL_image.h"
#include "glm/glm/glm.hpp"
#include "Entities/Entity.h"
#include "Components/Transform.h"

namespace Motherload
{
    // Forward declarations
    class Transform;

    class PhysicalEntity : public Entity
    {
    public:
        Transform* transform;
        SDL_Texture* texture;
    };
} // namespace Motherload
