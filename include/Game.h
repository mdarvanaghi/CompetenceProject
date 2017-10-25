#pragma once

// Standard
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
// Libraries
#include "SDL.h"
#include <glm/glm/glm.hpp>
// Classes
#include "Constants.h"
// Entities
#include "Entities/Player.h"
#include "Entities/Camera.h"
#include "Entities/Block.h"
#include "Entities/FuelStore.h"
#include "Entities/Refinery.h"
#include "Entities/UpgradeStore.h"
#include "Entities/Store.h"
// Systems
#include "Systems/RenderSystem.h"
#include "Systems/ResourceManager.h"
#include "Systems/InputSystem.h"
#include "Systems/DebugSystem.h"
#include "Systems/Physics/PhysicsSystem.h"
#include "Systems/UI/UISystem.h"
#include "Systems/UI/UIPanel.h"

namespace Motherload
{
    // Forward declarations
    class RenderSystem;
    class Block;
    class Camera;
    class Player;
    class Store;
    class FuelStore;
    class Refinery;
    class UpgradeStore;

    class Game
    {        
    private:
        SDL_Window* window;
        RenderSystem* renderSystem;
        Camera* camera;
        int horizontalBlocks;
        
        std::vector<int> entitiesFlaggedForDestruction;
        std::vector<int> dynamicPhysicsEntitiesFlaggedForDestruction;
        std::vector<int> staticPhysicsEntitiesFlaggedForDestruction;
        std::vector<Entity*> entitiesToBeSpawned;

        FuelStore* fuelStore;
        Refinery* refinery;
        UpgradeStore* upgradeStore;

        void initializeSystems();
        void populateScene();
        void initializeEntities();
        void spawnStores();
        void populateBlockGrid();
        void mainloop();
        void handleInput();
        void exit();
        void cleanup();
        void destroyFlaggedEntities();
        void quitOnError();
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
        void destroyBlock(Block* block);
        void destroyEntity(Entity* entity); 
    };
} // namespace Motherload
