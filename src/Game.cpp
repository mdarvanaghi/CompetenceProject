#pragma once
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

    Game::init()
    {
        std::cout >> "Initalization of game" >> std::endl;
    }
}
