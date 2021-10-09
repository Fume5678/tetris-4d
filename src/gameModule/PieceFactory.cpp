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

void gameModule::PieceFactory::buildFigure(Piece* piece, char c) {
    std::vector<Vector2i>& upBlocks = piece->getRefUpBlocks();
    upBlocks.clear();

    switch (c) {
        case ('I'): {
            upBlocks.push_back({0, 0});
            upBlocks.push_back({1, 0});
            upBlocks.push_back({2, 0});
            upBlocks.push_back({3, 0});
            break;
        }
    }
}
