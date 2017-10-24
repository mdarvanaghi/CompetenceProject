#include "Game.h"

namespace Motherload
{
    Game* Game::instance;
    
    Game::Game()
    {
        if (instance != nullptr)
        {
            std::cerr << "Multiple versions of the game has been initialized. Only a single instance is supported." << std::endl;
        }
        instance = this;
    }

    void Game::startup()
    {
        initializeSystems();
        populateScene();
        addUiPanels();
        mainloop();
        exit();
    }

    void Game::initializeSystems()
    {
        std::cout << "Initializing systems...";

        /* SDL SYSTEMS */
        if (SDL_Init(SDL_INIT_VIDEO) == -1)
        {
            quitOnError();
        }

        if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
        {
            quitOnError();
        }

        if (TTF_Init() == -1)
        {
            quitOnError();
        }
        
        window = SDL_CreateWindow
        (
            "Motherload",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            Constants::intitialWindowWidth,
            Constants::intitialWindowHeight,
            SDL_WINDOW_SHOWN
        );
        /* /SDL SYSTEMS */
        
        
        Camera::initialize();
        RenderSystem::initialize(window);
        UISystem::initialize();
        Physics::PhysicsSystem::initialize();
        DebugSystem::initialize();
        
        std::cout << " Done!" << std::endl;
    }

    void Game::populateScene()
    {
        populateBlockGrid();
        spawnStores();
        player = new Player
        (
            glm::vec2
            (
                Constants::intitialWindowWidth / 2 - 100.0f,
                -100.0f
            )
        );
        player->initialize();
        entities.push_back(player);
        dynamicPhysicsEntities.push_back(player);
    }
    void Game::spawnStores()
    {
        fuelStore = new FuelStore(Constants::fuelStorePosition, Constants::storeSize);
        fuelStore->initialize();
        entities.push_back(fuelStore);
        staticPhysicsEntities.push_back(fuelStore);

        refinery = new Refinery(Constants::refineryPosition, Constants::storeSize);
        refinery->initialize();
        entities.push_back(refinery);
        staticPhysicsEntities.push_back(refinery);

//        upgradeStore = new Store(Constants::upgradeStorePosition, glm::vec2(Constants::cellSize*3, Constants::cellSize*2));
//        upgradeStore->initialize(StoreType::UpgradeStore, "data/textures/upgradestore.png");
//        entities.push_back(upgradeStore);
//        staticPhysicsEntities.push_back(upgradeStore);
    }

    void Game::populateBlockGrid()
    {
        std::cout << "Generating blocks...";
        blocks = std::vector<std::vector<Block*>>(Constants::worldDepth);
        std::srand(SDL_GetPerformanceCounter());
        float randMax = (float) RAND_MAX;
        horizontalBlocks = (int) Constants::intitialWindowWidth / Constants::cellSize;
        for (int i = 0; i < Constants::worldDepth; i++)
        {
            blocks.at(i) = std::vector<Block*>();
            for (int j = 0; j < horizontalBlocks; j++)
            {
                float roll = (float) std::rand() / randMax;
                MineralType mineralType = MineralType::Dirt;
                if (roll < Constants::spawnChanceGold)
                {
                    mineralType = MineralType::Gold;
                }
                else if (roll < Constants::spawnChanceIron)
                {
                    mineralType = MineralType::Iron;
                }
                else if (roll < Constants::spawnChanceGranite)
                {
                    mineralType = MineralType::Granite;
                }
                Block* block = new Block
                (
                    glm::vec2(j * Constants::cellSize + Constants::cellSize / 2,
                    i * Constants::cellSize + Constants::cellSize / 2)
                );
                block->initialize(mineralType, glm::vec2(i, j));
                blocks.at(i).push_back(block);
                entities.push_back(block);
                staticPhysicsEntities.push_back(block);
            }
        }
        std::cout << " Done!" << std::endl;
    }

    void Game::addUiPanels()
    {
        depthPanel = UISystem::addPanel(Constants::depthPanelPosition, "Depth: 0", false);
        lowestDepthPanel = UISystem::addPanel(Constants::lowestDepthPanelPosition, "Lowest depth: 0", false);
        moneyPanel = UISystem::addPanel(Constants::moneyPanelPosition, "$20", true);
        granitePanel = UISystem::addPanel(Constants::granitePanelPosition, "Granite: 0", false);
        ironPanel = UISystem::addPanel(Constants::ironPanelPosition, "Iron: 0", false);
        goldPanel = UISystem::addPanel(Constants::goldPanelPosition, "Gold: 0", false);
        drillPanel = UISystem::addPanel(Constants::drillPanelPosition, "Drill level: 0", false);
        hullPanel = UISystem::addPanel(Constants::hullPanelPosition, "Hull level: 0", false);
        gastankPanel = UISystem::addPanel(Constants::gastankPanelPosition, "Gas tank level: 0", false);
    }

    void Game::mainloop()
    {
        Uint64 timeNow = SDL_GetPerformanceCounter();
        Uint64 timeLast = 0.0f;
        
        std::cout << "Starting game" << std::endl;
        while(!quit)
        {
            /* Update deltatime */
            timeLast = timeNow;
            timeNow = SDL_GetPerformanceCounter();
            deltaTime = glm::clamp(((timeNow - timeLast) / (float) SDL_GetPerformanceFrequency()), 0.0f, 1.0f);

            /* Handle player inputs */
            InputSystem::registerInputs();
            handleInput();

            /* Step physics system */
            Physics::PhysicsSystem::step(deltaTime);

            /* Update entities */
            for (auto& entity : entities)
            {
                entity->update(deltaTime);
            }
           
            /* Update debug system */
            DebugSystem::update(deltaTime);

            /* Update UI System */
            UISystem::update(deltaTime);

            /* Update camera position */
            camera->updatePosition(deltaTime);

            /* Render scene */
            renderSystem->renderScene();

            /* Destroy entities flagged for destruction */
            destroyFlaggedEntities();
        }
    }

    void Game::handleInput()
    {
        if (InputSystem::getKeyDown(SDL_SCANCODE_Q))
        {
            quit = true;
            return;
        }
    }

    
    void Game::cleanup()
    {
        blocks.clear();
        entities.clear();
        SDL_DestroyWindow(window);
    }

    void Game::destroyBlock(Block* block)
    {
        blocks[block->coordinates.x][block->coordinates.y] = nullptr;
        destroyEntity(block);
    }
    
    void Game::destroyEntity(Entity* entity)
    {
        int i = 0;
        for (auto& element : entities) 
        {
            if (element == entity)
            {
                entitiesFlaggedForDestruction.push_back(i);
            }
            i++;
        }
        
        i = 0;
        for (auto & element : dynamicPhysicsEntities) 
        {
            if (element == entity)
            {
                dynamicPhysicsEntitiesFlaggedForDestruction.push_back(i);
            }
            i++;
        }
        
        i = 0;
        for (auto & element : staticPhysicsEntities) 
        {
            if (element == entity)
            {
                staticPhysicsEntitiesFlaggedForDestruction.push_back(i);
            }
            i++;
        }
    }
    
    void Game::destroyFlaggedEntities()
    {
        std::sort(Game::instance->entitiesFlaggedForDestruction.begin(), Game::instance->entitiesFlaggedForDestruction.end());
        std::sort(Game::instance->dynamicPhysicsEntitiesFlaggedForDestruction.begin(), Game::instance->dynamicPhysicsEntitiesFlaggedForDestruction.end());
        std::sort(Game::instance->staticPhysicsEntitiesFlaggedForDestruction.begin(), Game::instance->staticPhysicsEntitiesFlaggedForDestruction.end());
        
        int index = 0;
        
        while (Game::instance->dynamicPhysicsEntitiesFlaggedForDestruction.size() > 0) 
        {
            index = Game::instance->dynamicPhysicsEntitiesFlaggedForDestruction.back();
            Game::instance->dynamicPhysicsEntities.erase(Game::instance->dynamicPhysicsEntities.begin() + index);
            Game::instance->dynamicPhysicsEntitiesFlaggedForDestruction.pop_back();
        }
        
        while (Game::instance->staticPhysicsEntitiesFlaggedForDestruction.size() > 0) 
        {
            index = Game::instance->staticPhysicsEntitiesFlaggedForDestruction.back();
            Game::instance->staticPhysicsEntities.erase(Game::instance->staticPhysicsEntities.begin() + index);
            Game::instance->staticPhysicsEntitiesFlaggedForDestruction.pop_back();
        }
        
        while (Game::instance->entitiesFlaggedForDestruction.size() > 0) 
        {
            index = Game::instance->entitiesFlaggedForDestruction.back();
            Game::instance->entities.erase(Game::instance->entities.begin() + index);
            Game::instance->entitiesFlaggedForDestruction.pop_back();
        }
    }
    
    void Game::quitOnError()
    {
        std::cerr << SDL_GetError() << std::endl;
        std::cout << "Terminating..." << std::endl;
        SDL_Quit();
    }
    
    void Game::exit()
    {
        cleanup();
        std::cout << "Quitting game" << std::endl;
        SDL_Quit();
    }
} // namespace Motherload
