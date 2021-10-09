#pragma once

#include <utility>
#include <vector>
#include <raylib.h>
#include "engineModule/Actor.h"
#include "gameModule/GameParams.h"

namespace gameModule {
    class PieceFactory;

    enum class Direction { UP, RIGHT, LEFT, DOWN };

    struct Vector2i {
        int x;
        int y;

        Vector2i& operator+(const Vector2i& other);

        Vector2i& operator+=(const Vector2i& other);

        Vector2i& operator+(int val);
        Vector2i& operator+=(int val);

        Vector2i& operator*(int val);
        Vector2i& operator*=(int val);
    };

    class Piece : public engineModule::Actor {
        friend PieceFactory;
        std::vector<Vector2i>& getRefUpBlocks();

    public:
        Piece(std::string name);
        ~Piece();

        void init();
        void action(float delta) override;
        void render(float delta) override;

        Vector2i getPosOnGrid();

    private:
        Color                 blocsColor;
        Vector2i              posOnGrid;
        std::vector<Vector2i> upBlocks;
        std::vector<Vector2i> rightBlocks;
        Direction             direct;
    };

} // namespace gameModule