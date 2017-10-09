#include "Game.h"
// Standard
#include <iostream>
#include <vector>
// Libraries
#include <SDL2/SDL.h>
#include <glm/glm/glm.hpp>

namespace Motherload
{
    Game* Game::instance;
    
    Game::Game()
    {
        if(instance != nullptr)
        {
            std::cerr << "Multiple versions of the game has been initialized. Only a single instance is supported." << std::endl;
        }
        std::cout << "Game constructor called" << std::endl;
        instance = this;
    }

    void Game::init()
    {
        // if (SDL_Init(SDL_INIT_VIDEO) == -1) // Initialize SDL2
        // {
        //     std::cout << SDL_GetError() << std::endl;
        // }
        std::cout << "Initalization of game" << std::endl;
    }
}
