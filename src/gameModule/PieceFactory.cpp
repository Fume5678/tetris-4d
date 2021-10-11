#include "PieceFactory.h"
#include "Piece.h"
#include <sstream>

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

Piece* gameModule::PieceFactory::buildFigure(char shape) {
    Piece* newPiece = new Piece;
    std::vector<Vector2i>& upBlocks = newPiece->getRefUpBlocks();
    std::vector<Vector2i>& leftBlocks = newPiece->getRefLeftBlocks();
    std::vector<Vector2i>& downBlocks = newPiece->getRefDownBlocks();
    std::vector<Vector2i>& rightBlocks = newPiece->getRefRightBlocks();
    upBlocks.clear();
    leftBlocks.clear();
    downBlocks.clear();
    rightBlocks.clear();

    // Hand work's for lohs
    switch (shape) {
        case ('I'): {
            upBlocks.push_back({-1, 0});
            upBlocks.push_back({0, 0});
            upBlocks.push_back({1, 0});
            upBlocks.push_back({2, 0});

            leftBlocks.push_back({0, -1});
            leftBlocks.push_back({0, 0});
            leftBlocks.push_back({0, 1});
            leftBlocks.push_back({0, 2});

            downBlocks = upBlocks;
            rightBlocks = leftBlocks;
            break;
        }
        case ('S'): {
            upBlocks.push_back({-1, 1});
            upBlocks.push_back({0, 1});
            upBlocks.push_back({0, 0});
            upBlocks.push_back({1, 0});

            leftBlocks.push_back({0, -1});
            leftBlocks.push_back({0, 0});
            leftBlocks.push_back({1, 0});
            leftBlocks.push_back({1, 1});

            downBlocks = upBlocks;
            rightBlocks = leftBlocks;
            break;
        }
        case ('Z'): {
            upBlocks.push_back({ -1, 0 });
            upBlocks.push_back({ 0, 0});
            upBlocks.push_back({ 0, 1 });
            upBlocks.push_back({ 1, 1 });

            leftBlocks.push_back({ 1,  -1});
            leftBlocks.push_back({ 1, 0 });
            leftBlocks.push_back({ 0, 0 });
            leftBlocks.push_back({ 0, 1 });

            downBlocks = upBlocks;
            rightBlocks = leftBlocks;
            break;
        }
        case ('L'): {
            upBlocks.push_back({ -1, 0 });
            upBlocks.push_back({ 0, 0 });
            upBlocks.push_back({ 1, 0 });
            upBlocks.push_back({ 1, -1 });

            leftBlocks.push_back({ 0,  -1 });
            leftBlocks.push_back({ 0, 0 });
            leftBlocks.push_back({ 0, 1 });
            leftBlocks.push_back({ 1, 1 });

            downBlocks.push_back({-1, 1});
            downBlocks.push_back({-1, 0});
            downBlocks.push_back({0, 0});
            downBlocks.push_back({1, 0});

            rightBlocks.push_back({ -1, -1 });
            rightBlocks.push_back({ 0, -1});
            rightBlocks.push_back({ 0,  0});
            rightBlocks.push_back({ 0,  1});
            break;
        }
        case ('J'): {
            upBlocks.push_back({ -1, -1 });
            upBlocks.push_back({ -1, 0 });
            upBlocks.push_back({ 0, 0 });
            upBlocks.push_back({  1, 0 });

            rightBlocks.push_back({ 1,  -1 });
            rightBlocks.push_back({ 0, -1 });
            rightBlocks.push_back({ 0, 0 });
            rightBlocks.push_back({ 0, 1 });

            downBlocks.push_back({ -1, 0 });
            downBlocks.push_back({ 0, 0 });
            downBlocks.push_back({ 1, 0 });
            downBlocks.push_back({ 1, 1 });

            leftBlocks.push_back({ 0, -1 });
            leftBlocks.push_back({ 0, 0 });
            leftBlocks.push_back({ 0,  1 });
            leftBlocks.push_back({ -1,  1 });
            break;
        }

        case ('O'): {
            upBlocks.push_back({ -1, -1 });
            upBlocks.push_back({ 0, -1 });
            upBlocks.push_back({ 0, 0 });
            upBlocks.push_back({ -1, 0});

            rightBlocks = upBlocks;

            downBlocks = upBlocks;

            leftBlocks = upBlocks;
            break;
        }

        case ('T'): {
            upBlocks.push_back({ -1, 0 });
            upBlocks.push_back({ 0, 0 });
            upBlocks.push_back({ 0, -1 });
            upBlocks.push_back({ 1, 0 });

            leftBlocks.push_back({ 0, -1 });
            leftBlocks.push_back({ 0, 0 });
            leftBlocks.push_back({ 1, 0 });
            leftBlocks.push_back({ 0, 1 });

            downBlocks.push_back({ -1, 0 });
            downBlocks.push_back({ 0, 0 });
            downBlocks.push_back({ 0, 1});
            downBlocks.push_back({ 1, 0 });

            rightBlocks.push_back({ 0, -1 });
            rightBlocks.push_back({ 0, 0 });
            rightBlocks.push_back({-1, 0 });
            rightBlocks.push_back({ 0, 1 });
            break;
        }
    }

    std::stringstream sstr;
    sstr << "Piece_" << newPiece;
    newPiece->setName(sstr.str());
    return newPiece;
}
