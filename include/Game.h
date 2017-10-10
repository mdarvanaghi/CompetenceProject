#ifndef GAME_H
#define GAME_H
// Standard
#include <iostream>
#include <vector>
// Libraries
#include <SDL2/SDL.h>
#include <glm/glm/glm.hpp>
// Headers
#include "Entities/Block.h"
#include "Entities/Player.h"

namespace Motherload
{
    class Game
    {        
    public:
        // Variables
        static Game* instance;
        float deltaTime;
        float time;

        // Methods
        Game();
        void init();
    };
} // namespace Motherload
#endif
