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
        mainloop();
        exit();
    }

    void Game::initializeSystems()
    {
        std::cout << "Initializing systems...";
        if (SDL_Init(SDL_INIT_VIDEO) == -1)
        {
            quitOnError();
        }

        if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
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

        Camera::initialize();
        renderSystem = new RenderSystem();
        renderSystem->initialize(window);
        std::cout << " Done!" << std::endl;
    }

    void Game::populateScene()
    {
        populateBlockGrid();
    }

    void Game::populateBlockGrid()
    {
        std::cout << "Generating blocks...";
        blocks = std::vector<std::vector<Block*>>(Constants::worldDepth);
        // TODO: Seed rand() with srand()
        float randMax = (float) RAND_MAX;
        horizontalBlocks = (int) Constants::intitialWindowWidth / Constants::cellSize;
        for (int i = 0; i < Constants::worldDepth; i++)
        {
            blocks.at(i) = std::vector<Block*>();
            for (int j = 0; j < horizontalBlocks; j++)
            {
                MineralType mineralType = MineralType::Dirt;
                float roll = (float) std::rand() / randMax;
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
                Block* block = new Block(glm::vec2(j * Constants::cellSize, i * Constants::cellSize));
                block->initialize(mineralType);
                blocks.at(i).push_back(block);
                entities.push_back(block);
            }
        }
        std::cout << " Done!" << std::endl;
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
            std::cout << "FPS: " << 1 / deltaTime << std::endl;

            /* Get player inputs */
            InputSystem::registerInputs();
            handleInput();

            /* Update camera position */
            camera->updatePosition();

            /* Render scene */
            renderSystem->renderScene();
        }
    }

    void Game::handleInput()
    {
        if (InputSystem::getKeyDown(SDL_SCANCODE_Q))
        {
            quit = true;
        }
        if (InputSystem::getKeyDown(SDL_SCANCODE_F12))
        {
            debugMode = !debugMode;
        }
    }

    void Game::exit()
    {
        cleanup();
        std::cout << "Quitting game" << std::endl;
        SDL_Quit();
    }

    void Game::cleanup()
    {
        blocks.clear();
        entities.clear();
        SDL_DestroyWindow(window);
    }

    void Game::quitOnError()
    {
        std::cerr << SDL_GetError() << std::endl;
        std::cout << "Terminating..." << std::endl;
        SDL_Quit();
    }
} // namespace Motherload
