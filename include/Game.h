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

namespace Motherload
{
    class Game
    {        
    private:
        SDL_Window *window;

        std::vector<Entity> entities;
        std::vector<Entity> entitiesFlaggedForRemoval;
        std::vector<Entity> entitiesToBeSpawned;
    public:
        // Variables
        static Game* instance;
        float deltaTime;
        float time;

        // Methods
        Game();
        void initialize();
        void mainloop();
        void exit();
        void cleanup();
    };
} // namespace Motherload
