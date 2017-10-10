#pragma once

// Standard
#include <iostream>
#include <vector>
// Libraries
#include "SDL.h"
#include <glm/glm/glm.hpp>
// Headers
#include "Entities/Block.h"
#include "Entities/Player.h"
#include "Constants.h"
#include "Systems/RenderSystem.h"

namespace Motherload
{
    class Game
    {        
    private:
        SDL_Window* window;
        RenderSystem* renderSystem;
        
        std::vector<int> entitiesFlaggedForRemoval;
        std::vector<Entity*> entitiesToBeSpawned;
    public:

        std::vector<Entity*> entities;

        // Variables
        static Game* instance;
        float deltaTime;
        float time;

        // Methods
        Game();
        void startup();
        void initializeSystems();
        void mainloop();
        void exit();
        void cleanup();
        static void quitOnError();
    };
} // namespace Motherload
