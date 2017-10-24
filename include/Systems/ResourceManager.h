#pragma once

#include <string>
#include <map>
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Systems/RenderSystem.h"

namespace Motherload
{
    class ResourceManager
    {
    private:
        static std::map<std::string, SDL_Texture*> textures;
        static std::map<std::string, TTF_Font*> fonts;

    public:
        static SDL_Texture* getTexture(std::string name);
        static TTF_Font* getFont(std::string name);
    };
} // namespace Motherload
