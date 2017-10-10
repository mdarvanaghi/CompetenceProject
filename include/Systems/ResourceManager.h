#pragma once

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "SDL_image.h"
#include "RenderSystem.h"

namespace Motherload
{
    class ResourceManager
    {
    private:
        static std::map<std::string, SDL_Texture*> textures;

        static SDL_Texture* loadTexture(const std::string &file);
    public:
        static SDL_Texture* getTexture(std::string name);
    };
} // namespace Motherload
