#ifndef GAME_H
#define GAME_H

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
