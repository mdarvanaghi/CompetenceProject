#pragma once

#include "SDL2/SDL_image.h"
#include "Components/Transform.h"

namespace Motherload
{
    // Forward declarations
    class Transform;
    
    class Entity
    {
    public:
        const char* name;
        Transform* transform;
        SDL_Texture* texture;

        virtual void initialize() {}
        virtual void update(float deltaTime) {}
    };
} // namespace Motherload
