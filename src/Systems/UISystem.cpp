#include "Systems/UISystem.h"

namespace Motherload
{
    SDL_Surface* UISystem::surface;
    TTF_Font* UISystem::font;

    void UISystem::initialize()
    {
        font = TTF_OpenFont("Sans.ttf", 24);
    }

} // namespace Motherload

