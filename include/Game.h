#pragma once

#include "include.h"

namespace Motherload
{
    class Game
    {
    private:
        
        
    public:
        static Game* instance;
        float deltaTime;
        float time;
        Game();
        void init();
    };
}
