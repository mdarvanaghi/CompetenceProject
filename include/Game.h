#pragma once

// Standard
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Libraries
#include "SDL.h"
#include <glm/glm/glm.hpp>
// Classes
#include "Constants.h"
// Entities
#include "Entities/Block.h"
#include "Entities/Player.h"
// Systems
#include "Systems/RenderSystem.h"
#include "Systems/ResourceManager.h"
#include "Systems/InputSystem.h"
#include "Entities/Camera.h"

namespace Motherload
{
    class Game
    {        
    private:
        SDL_Window* window;
        RenderSystem* renderSystem;
        Camera* camera;
        int horizontalBlocks = 0;
        bool quit = 0;
        
        std::vector<int> entitiesFlaggedForRemoval;
        std::vector<Entity*> entitiesToBeSpawned;
    public:
        // Variables
        std::vector<Entity*> entities;
        std::vector<std::vector<Block*>> blocks;

        static Game* instance;
        float deltaTime;
        float time;
        bool debugMode = 0;

        // Methods
        Game();
        void startup();
        void initializeSystems();
        void populateScene();
        void populateBlockGrid();
        void mainloop();
        void handleInput();
        void exit();
        void cleanup();
        static void quitOnError();
    };
} // namespace Motherload
