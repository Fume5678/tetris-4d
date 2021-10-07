#include "GameParams.h"

using namespace gameModule;

int GameParams::cellSize{ 24 };
int GameParams::stepDelay{ 23 };
std::pair<int, int>  GameParams::gridSize{ 30, 30 };

 int GameParams::getCellSizePx() {
    return cellSize;
}

// Size of cell in fps 
 int GameParams::getStepDelayMs() {
    return stepDelay;
}

 int GameParams::getStepDelayFrames() {
    int x = engineModule::EngineParams::getFps();
    int y = x * stepDelay / 1000; // 1000 ms 

    return y;
}

 std::pair<int, int> GameParams::getGridSize() {
    return gridSize;
}