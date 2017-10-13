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
#include "Entities/Player.h"
#include "Entities/Camera.h"
#include "Entities/Block.h"
// Systems
#include "Systems/RenderSystem.h"
#include "Systems/ResourceManager.h"
#include "Systems/InputSystem.h"
#include "Systems/DebugSystem.h"
#include "Systems/Physics/PhysicsSystem.h"

namespace Motherload
{
    // Forward declarations
    class RenderSystem;
    class Block;
    class Camera;
    class Player;

    class Game
    {        
    private:
        SDL_Window* window;
        RenderSystem* renderSystem;
        Camera* camera;
        int horizontalBlocks = 0;
        
        std::vector<int> entitiesFlaggedForRemoval;
        std::vector<Entity*> entitiesToBeSpawned;
    public:
        // Variables
        Player* player;
        std::vector<Entity*> entities;
        std::vector<Physics::PhysicsEntity*> dynamicPhysicsEntities;
        std::vector<Physics::PhysicsEntity*> staticPhysicsEntities;
        std::vector<std::vector<Block*>> blocks;
        bool quit = 0;

        static Game* instance;
        float deltaTime;
        float time;

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
