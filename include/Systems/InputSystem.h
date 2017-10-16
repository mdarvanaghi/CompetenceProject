#pragma once

#include "SDL.h"
#include <map>
#include <iostream>
#include "Game.h"

namespace Motherload
{
    class InputSystem
    {
    private:
        // Variables
        static std::map<SDL_Scancode, bool> downKeys;
        static std::map<SDL_Scancode, bool> heldKeys;
        static std::map<SDL_Scancode, bool> upKeys;
    
        // Methods
        static void keyUpEvent(const SDL_Event& event);
        static void keyDownEvent(const SDL_Event& event);
        static void clearMaps();

    public:
        static void registerInputs();
        static bool getKeyDown(SDL_Scancode key);
        static bool getKey(SDL_Scancode key);
        static bool getKeyUp(SDL_Scancode key);
    };
}