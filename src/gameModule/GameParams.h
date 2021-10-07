#pragma once

#include "engineModule/EngineParams.h"
#include <iostream>

namespace gameModule {
    class GameParams {
    public:
        // Size of cell in px 
        static int getCellSize();

        // Size of cell in fps 
        static int getStepDelayMs();

        static int getStepDelayFrames() ;

        static std::pair<int, int> getGridSize();

    private:
        static int cellSize;
        static int stepDelay;
        static std::pair<int, int> gridSize;
    };

} // namespace gameModule