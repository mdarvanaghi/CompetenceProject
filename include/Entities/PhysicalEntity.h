#pragma once

#include "Entities/Entity.h"
#include "SDL_image.h"
#include "glm/glm/glm.hpp"

namespace Motherload
{
    class PhysicalEntity : public Entity
    {
    private:
        
    public:
        glm::vec2 position;
        SDL_Texture* texture;
    };
} // namespace Motherload
