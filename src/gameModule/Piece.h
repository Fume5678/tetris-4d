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
        std::vector<Vector2i>& getRefRightBlocks();
        std::vector<Vector2i>& getRefDownBlocks();
        std::vector<Vector2i>& getRefLeftBlocks();

    public:
        Piece(std::string name);
        ~Piece();

        void init();
        void action(float delta) override;
        void render(float delta) override;
        void rotateLeft();
        void rotateRight();

        Vector2i getPosOnGrid();
        std::vector<Vector2i>* getCurrentBlocks();

    private:
        Color                 blocsColor;
        Vector2i              posOnGrid;
        std::vector<Vector2i> upBlocks;
        std::vector<Vector2i> rightBlocks;
        std::vector<Vector2i> leftBlocks;
        std::vector<Vector2i> downBlocks;
        std::vector<Vector2i>* p_currentBlocks;
    };

} // namespace gameModule