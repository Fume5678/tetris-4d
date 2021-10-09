#include "PieceFactory.h"
#include "Piece.h"

using namespace gameModule;

PieceFactory* PieceFactory::instance{};

gameModule::PieceFactory::PieceFactory() {}

gameModule::PieceFactory::~PieceFactory() {}

PieceFactory* gameModule::PieceFactory::getInstance() {
    if (instance) {
        return instance;
    }

    instance = new PieceFactory;
    return instance;
}

void gameModule::PieceFactory::buildFigure(Piece* piece, char shape) {
    std::vector<Vector2i>& upBlocks = piece->getRefUpBlocks();
    std::vector<Vector2i>& leftBlocks = piece->getRefLeftBlocks();
    std::vector<Vector2i>& downBlocks = piece->getRefDownBlocks();
    std::vector<Vector2i>& rightBlocks = piece->getRefRightBlocks();
    upBlocks.clear();
    leftBlocks.clear();
    downBlocks.clear();
    rightBlocks.clear();

    // Hand work's for lohs
    switch (shape) {
        case ('I'): {
            upBlocks.push_back({0, 0});
            upBlocks.push_back({1, 0});
            upBlocks.push_back({2, 0});
            upBlocks.push_back({3, 0});

            leftBlocks.push_back({0, 0});
            leftBlocks.push_back({0, 1});
            leftBlocks.push_back({0, 2});
            leftBlocks.push_back({0, 3});

            downBlocks = upBlocks;
            rightBlocks = leftBlocks;
            break;
        }
        case ('S'): {
            upBlocks.push_back({0, 1});
            upBlocks.push_back({1, 1});
            upBlocks.push_back({1, 0});
            upBlocks.push_back({2, 0});

            leftBlocks.push_back({0, 0});
            leftBlocks.push_back({0, 1});
            leftBlocks.push_back({1, 1});
            leftBlocks.push_back({1, 2});

            downBlocks = upBlocks;
            rightBlocks = leftBlocks;
            break;
        }
    }
}
