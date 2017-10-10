#include "Game.h"

namespace Motherload
{
    Game* Game::instance;
    
    Game::Game()
    {
        if(instance != nullptr)
        {
            std::cerr << "Multiple versions of the game has been initialized. Only a single instance is supported." << std::endl;
        }
        instance = this;
    }

    void Game::initialize()
    {
        std::cout << "Initializing game" << std::endl;
        if (SDL_Init(SDL_INIT_VIDEO) == -1) // Initialize SDL2
        {
            std::cout << SDL_GetError() << std::endl;
        }
        
        window = SDL_CreateWindow
        (
            "Motherload",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            Constants::intitialWindowWidth,
            Constants::intitialWindowHeight,
            0
        );

        // Run mainloop
        mainloop();
        exit();
    }

    void Game::mainloop()
    {
        bool quit;
        while(!quit)
        {
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
        SDL_DestroyWindow(window);
    }
} // namespace Motherload
