#include "Systems/ResourceManager.h"

namespace Motherload
{
    std::map<std::string, SDL_Texture*> ResourceManager::textures;
    std::map<std::string, TTF_Font*> ResourceManager::fonts;
    
    SDL_Texture* ResourceManager::getTexture(std::string name)
    {
        if (ResourceManager::textures[name] == nullptr)
        {
            ResourceManager::textures[name] = RenderSystem::loadTexture(name);
        }
        return ResourceManager::textures[name];
    }

    TTF_Font* ResourceManager::getFont(std::string name)
    {
        if (ResourceManager::fonts[name] == nullptr)
        {
            ResourceManager::fonts[name] = TTF_OpenFont(name.c_str(), Constants::fontSize);
        }
        return ResourceManager::fonts[name];
    }
}