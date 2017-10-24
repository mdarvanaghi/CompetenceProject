#pragma once
#include <string>
#include "SDL.h"
#include "Entities/Store.h"
#include "Systems/UI/UIPanel.h"

namespace Motherload
{
    class Refinery : public Store
    {
    private:
        std::vector<std::string> buyStrings;
        int granitePrice;
        int ironPrice;
        int goldPrice;

        void updateUi();
    public:
        Refinery(glm::vec2 position, glm::vec2 size);
        void initialize();
    };
} // namespace Motherload
