#include "Systems/InputSystem.h"


namespace Motherload
{
    // Forward declaration of maps
    std::map<SDL_Scancode, bool> InputSystem::downKeys;
    std::map<SDL_Scancode, bool> InputSystem::heldKeys;
    std::map<SDL_Scancode, bool> InputSystem::upKeys; 

    void InputSystem::keyDownEvent(const SDL_Event& event) 
    {
        downKeys[event.key.keysym.scancode] = true;
        heldKeys[event.key.keysym.scancode] = true;
    }
    
    void InputSystem::keyUpEvent(const SDL_Event& event) 
    {
        heldKeys[event.key.keysym.scancode] = false;
        upKeys[event.key.keysym.scancode] = true;
    }

    void InputSystem::registerInputs()
    {
        downKeys.clear();
        upKeys.clear();

        SDL_Event sdlEvent;
        while (SDL_PollEvent(&sdlEvent)) 
        {
            switch (sdlEvent.type)
            {
                case SDL_KEYDOWN:
                {
                    if (sdlEvent.key.repeat == 0) 
                    {
                        keyDownEvent(sdlEvent);
                    }
                    break;
                }

                case SDL_QUIT:
                {
                    Game::instance->quit = true;
                    break;
                }
    
                case SDL_KEYUP:
                {
                    keyUpEvent(sdlEvent);
                    break;
                }

                default:
                    break;
            }
        }
    }

    bool InputSystem::getKeyDown(SDL_Scancode key)
    {
        return downKeys[key];
    }

    bool InputSystem::getKey(SDL_Scancode key)
    {
        return heldKeys[key];
    }

    bool InputSystem::getKeyUp(SDL_Scancode key)
    {
        return upKeys[key];
    }
}