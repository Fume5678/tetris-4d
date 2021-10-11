#pragma once
#include <vector>
#include <string>
#include <raylib.h>
#include "engineModule/Actor.h"

namespace gameModule {

    class Piece;
    using GridTable = bool[30][30];

    class Game : public engineModule::Actor {
    public:
        Game(std::string name);
        ~Game();

        void init();

        void action(float delta) override;
        void render(float delta) override;
        void onDestroy() override;
        void destroyPiece();
        void spawnPiece();
        void respawn();
        void resetGrid();
        void endGame();
        void movePiece();

        bool isCollide(int directX, int directY);
        bool isLose();

    private:
        Music                   music;
        bool                    gameRun;
        GridTable               gridTable;
        std::pair<float, float> screenSize;
        Texture2D               bg;
        long                    currentTick;
        uint32_t                delayStartRedRing;
        Rectangle               redRing;
        int                     redRingSize;
        Rectangle               blueRing;
        Rectangle               gridRect;
        Piece*                  activePiece;
        int                     score;
    };
} // namespace gameModule