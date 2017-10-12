#pragma once

#include "SDL_image.h"
#include "Components/Transform.h"

namespace Motherload
{
    class Entity
    {
    public:
        Transform* transform;
        SDL_Texture* texture;

        virtual void initialize() {}
        virtual void update() {}
    };
} // namespace Motherload
