#pragma once

#include "SDL.h"
#include <iostream>
#include "SDL_image.h"
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
        
        ~Entity()
        {
            delete name;
            delete transform;
            std::cout << "Destroyed!" << std::endl;
        }
        virtual void initialize() {}
        virtual void update(float deltaTime) {}
    };
} // namespace Motherload
