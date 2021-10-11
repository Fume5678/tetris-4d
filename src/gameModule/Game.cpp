
#include <array>

#include "gameModule/GameParams.h"
#include "Game.h"
#include "gameModule/Piece.h"
#include "gameModule/PieceFactory.h"

#define MOVE_DELAY 3
#define REDRING_STEP_DELAY 30
#define REDRING_START_DELAY 50

using namespace gameModule;
using namespace engineModule;

Game::Game(std::string name)
    : Actor{name}, gridTable{}, currentTick{}, delayStartRedRing{
                                                   REDRING_START_DELAY} {
    screenSize = ::EngineParams::getScreenResolution();
    EngineParams::setShowFps(true);

    resetGrid();

    init();
}

gameModule::Game::~Game() {}

void Game::init() {
    bg        = LoadTexture(ASSETS_PATH "background.png");
    bg.width  = ::EngineParams::getScreenWidth();
    bg.height = ::EngineParams::getScreenHeight();

    gridRect.width  = GameParams::getCellSizePx();
    gridRect.height = GameParams::getCellSizePx();

    // Blue ring
    blueRing.width  = GameParams::getCellSizePx() * 24; // 24 - blue ring size;
    blueRing.height = GameParams::getCellSizePx() * 24;
    blueRing.x      = screenSize.first / 2 - blueRing.width / 2;
    blueRing.y      = screenSize.second / 2 - blueRing.height / 2;

    resetGame();
}

void gameModule::Game::action(float delta) {

    if (!gameRun) {
        endGame();
        return;
    }

    gameRun = !isLose();

    currentTick++;
    movePiece();

    // RedRing
    if (delayStartRedRing == 0) {
        if (currentTick % REDRING_STEP_DELAY == 0) {
            redRing.x += GameParams::getCellSizePx();
            redRing.y += GameParams::getCellSizePx();
            redRing.width -= GameParams::getCellSizePx() * 2;
            redRing.height -= GameParams::getCellSizePx() * 2;
        }
    } else {
        delayStartRedRing--;
    }

    // TODO: checking for circle around earth

    // Reset ticker
    if (currentTick == UINT64_MAX) {
        currentTick = 0;
    }
}

void gameModule::Game::render(float delta) {
    DrawTexture(bg, 0, 0, WHITE);

    // TODO: optimize grid drawing
    for (int i = 0; i < 30; ++i) {
        for (int j = 0; j < 30; ++j) {
            gridRect.x = i * GameParams::getCellSizePx() + getX();
            gridRect.y = j * GameParams::getCellSizePx() + getY();
            if (!gridTable[i][j]) {
                DrawRectangleLinesEx(gridRect, 0.5, LIGHTGRAY);
            } else {
                if (11 <= i && i < 19 && 11 <= j && j < 19) {
                    DrawRectangle(gridRect.x,
                                  gridRect.y,
                                  gridRect.width,
                                  gridRect.height,
                                  BLACK);
                } else {
                    DrawRectangle(gridRect.x,
                                  gridRect.y,
                                  gridRect.width,
                                  gridRect.height,
                                  GRAY);
                }
            }
            DrawText(
                std::to_string(i).c_str(), gridRect.x, gridRect.y, 9, WHITE);
        }
    }

    DrawRectangleLinesEx(blueRing, 3, BLUE);
    DrawRectangleLinesEx(redRing, 3, RED);
    DrawRectangleLinesEx(redRing, 3, RED);

    if (!gameRun) {
        DrawText("Game over\npress R to restart",
                 EngineParams::getScreenWidth() / 2,
                 EngineParams::getScreenHeight()/2,
                 42,
                 RED);

    }
}

void Game::destroyPiece() {
    if (!activePiece) {
        return;
    }

    auto coords = activePiece->getGlobalBlocksCoords();
    for (const auto& crd : coords) {
        if (crd.x >= 0 && crd.x < GameParams::getGridSize().first &&
            crd.y >= 0 && crd.y < GameParams::getGridSize().second) {
            gridTable[crd.x][crd.y] = true;
        }
    }

    removeChild(activePiece);
    delete activePiece;
    activePiece = nullptr;

    // Reset red ring
    redRing.width  = GameParams::getCellSizePx() * 30; // 30 - red ring size
    redRing.height = GameParams::getCellSizePx() * 30;
    redRing.x      = screenSize.first / 2 - redRing.width / 2;
    redRing.y      = screenSize.second / 2 - redRing.height / 2;

    delayStartRedRing = REDRING_START_DELAY;
    resetGame();
}

void gameModule::Game::spawnPiece() {
    if (activePiece) {
        TraceLog(LOG_ERROR, "Piece already create");
    }

    char shape = std::array<char, 3>{'T'}[rand() % 1];

    int      randInd    = rand() % 4;
    Vector2i startPoint = std::array<Vector2i, 4>{Vector2i{14, 2},
                                                  Vector2i{1, 14},
                                                  Vector2i{14, 28},
                                                  Vector2i{28, 14}}[randInd];

    activePiece = PieceFactory::getInstance()->buildFigure(shape);
    activePiece->setPosOnGrid(startPoint.x, startPoint.y);
    activePiece->setXY(redRing.x, redRing.y);
    if (randInd % 2 != 0) {
        activePiece->rotateLeft();
    }
    addChild(activePiece);
}

void gameModule::Game::resetGame() {
    gameRun        = true;
    redRing.width  = GameParams::getCellSizePx() * 30; // 30 - red ring size
    redRing.height = GameParams::getCellSizePx() * 30;
    redRing.x      = screenSize.first / 2 - redRing.width / 2;
    redRing.y      = screenSize.second / 2 - redRing.height / 2;

    setX(redRing.x);
    setY(redRing.y);

    spawnPiece();
}

void gameModule::Game::resetGrid() {
    for (size_t i = 0; i < GameParams::getGridSize().first; ++i) {
        for (size_t j = 0; j < GameParams::getGridSize().second; ++j) {
            // Starting blacksqare
            if (11 <= i && i < 19 && 11 <= j && j < 19) {
                gridTable[i][j] = true;
            } else {
                gridTable[i][j] = false;
            }
        }
    }
}

void gameModule::Game::endGame() {
    if (IsKeyPressed(KEY_R)) {
        destroyPiece();
        resetGrid();
    }
    std::cout << "GameLose\n";
}

void Game::movePiece() {
    if (!activePiece) {
        return;
    }

    // Move piece

    // Left
    if (IsKeyPressed(KEY_D)) {
        TraceLog(LOG_INFO, "Right");
        if (isCollide(1, 0)) {
            destroyPiece();
            return;
        }
        activePiece->moveOnGrid(1, 0);
    }

    // Right
    if (IsKeyPressed(KEY_A)) {
        TraceLog(LOG_INFO, "Left");
        if (isCollide(-1, 0)) {
            destroyPiece();
        }
        activePiece->moveOnGrid(-1, 0);
    }
    // Up
    if (IsKeyPressed(KEY_W)) {
        TraceLog(LOG_INFO, "Up");
        if (isCollide(0, -1)) {
            destroyPiece();
            return;
        }
        activePiece->moveOnGrid(0, -1);
    }
    // Down
    if (IsKeyPressed(KEY_S)) {
        TraceLog(LOG_INFO, "Down");
        if (isCollide(0, 1)) {
            destroyPiece();
            return;
        }
        activePiece->moveOnGrid(0, 1);
    }

    if (IsKeyPressed(KEY_Q)) {
        activePiece->rotateLeft();
    }

    if (IsKeyPressed(KEY_E)) {
        activePiece->rotateRight();
    }
}

bool gameModule::Game::isCollide(int directX, int directY) {
    if (!activePiece) {
        return false;
    }

    std::vector<Vector2i> pieceBlocksCoord =
        activePiece->getGlobalBlocksCoords();
    for (const auto& coord : pieceBlocksCoord) {
        if (coord.x + directX < 0 ||
            coord.x + directX >= GameParams::getGridSize().first ||
            coord.y + directY < 0 ||
            coord.y + directY >= GameParams::getGridSize().second) {
            return true;
        }
        if (gridTable[coord.x + directX][coord.y + directY]) {
            return true;
        }
    }

    return false;
}

bool gameModule::Game::isLose() {
    for (int i = 0; i < 30; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (gridTable[i][j]) {
                return true;
            }
        }
        for (int j = 26; j < 30; ++j) {
            if (gridTable[i][j]) {
                return true;
            }
        }
    }

    for (int j = 0; j < 30; ++j) {
        for (int i = 0; i < 4; ++i) {
            if (gridTable[i][j]) {
                return true;
            }
        }
        for (int i = 26; i < 30; ++i) {
            if (gridTable[i][j]) {
                return true;
            }
        }
    }

    return false;
}
