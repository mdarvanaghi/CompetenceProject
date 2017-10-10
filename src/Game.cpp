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
        std::cout << "Initializing systems..." << std::endl;
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

        renderSystem = new RenderSystem();
        renderSystem->initialize(window);
    }

    void Game::populateScene()
    {
        populateBlockGrid();
    }

    void Game::populateBlockGrid()
    {
        blocks = std::vector<std::vector<Block*>>(Constants::worldDepth);
        // TODO: Seed rand() with srand()
        float randMax = (float) RAND_MAX;
        horizontalBlocks = (int) Constants::intitialWindowWidth / Constants::cellSize;
        for (int i = 0; i < Constants::worldDepth; i++)
        {
            blocks.at(i) = std::vector<Block*>();
            for (int j = 0; j < horizontalBlocks; j++)
            {
                MineralType mineralType;
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
                else
                {
                    mineralType = MineralType::Dirt;
                }
                Block* block = new Block(mineralType);
                blocks.at(i).push_back(block);
                entities.push_back(block);
            }
        }
    }

    void Game::mainloop()
    {
        bool quit;
        
        while(!quit)
        {
            /* TEXTURE TEST */
            renderSystem->renderScene();
            // TODO: Make input system
            SDL_Event sdlEvent;
            while (SDL_PollEvent(&sdlEvent)) 
            {
                switch (sdlEvent.type)
                {
                    case SDL_KEYDOWN:
                        if (sdlEvent.key.repeat == 0) 
                        {
                            if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_Q)
                            {
                                // Exit game on Q
                                quit = true;
                            }
                        }
                        break;
                }
            }
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
        SDL_DestroyWindow(window);
    }

    void Game::quitOnError()
    {
        std::cerr << SDL_GetError() << std::endl;
        std::cout << "Terminating..." << std::endl;
        SDL_Quit();
    }
} // namespace Motherload
