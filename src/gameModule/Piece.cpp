#include "Piece.h"
#include <array>

using namespace gameModule;

gameModule::Piece::Piece(std::string name)
    : Actor{name}, posOnGrid{}, direct{Direction::UP} {
    init();
}

std::vector<Vector2i>& gameModule::Piece::getRefUpBlocks() {
    return upBlocks;
}

gameModule::Piece::~Piece() {}

void gameModule::Piece::init() {
    blocsColor = std::array<Color, 6>{
        RED, GREEN, DARKBLUE, VIOLET, GOLD, PINK}[rand() % 6];
}

void Piece::action(float delta) {}

void gameModule::Piece::render(float delta) {

    switch (direct) {
        case (Direction::UP): {
            for (size_t i = 0; i < upBlocks.size(); ++i) {
                DrawRectangle(upBlocks[i].x * GameParams::getCellSizePx() + getX(),
                              upBlocks[i].y * GameParams::getCellSizePx() + getY(),
                              GameParams::getCellSizePx(),
                              GameParams::getCellSizePx(),
                              blocsColor);
            }
            break;
        }
    }
}

Vector2i gameModule::Piece::getPosOnGrid() {
    return posOnGrid;
}

Vector2i& gameModule::Vector2i::operator+(const Vector2i& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vector2i& gameModule::Vector2i::operator+=(const Vector2i& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vector2i& gameModule::Vector2i::operator+(int val) {
    x += val;
    y += val;
    return *this;
}

Vector2i& gameModule::Vector2i::operator+=(int val) {
    x += val;
    y += val;
    return *this;
}

Vector2i& gameModule::Vector2i::operator*(int val) {
    x *= val;
    y *= val;
    return *this;
}

Vector2i& gameModule::Vector2i::operator*=(int val) {
    x *= val;
    y *= val;
    return *this;
}
