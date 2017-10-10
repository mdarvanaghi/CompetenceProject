#include "Systems/ResourceManager.h"

namespace Motherload
{
    std::map<std::string, SDL_Texture*> ResourceManager::textures;
    
    SDL_Texture* ResourceManager::getTexture(std::string name)
    {
        if (ResourceManager::textures[name] == nullptr)
        {
            ResourceManager::textures[name] = RenderSystem::loadTexture(name);
        }
        return ResourceManager::textures[name];
    }
}