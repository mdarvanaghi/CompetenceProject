#pragma once
#include <string>
#include "SDL.h"
#include "Entities/Store.h"
#include "Systems/UI/UIPanel.h"

namespace Motherload
{
    class FuelStore : public Store
    {
    private:
        int fuelPrice;
        std::string buyString;
        void updateUi();
    public:
        FuelStore(glm::vec2 position, glm::vec2 size);
        void initialize();
    };
} // namespace Motherload
