#include "Piece.h"
#include <array>

using namespace gameModule;

gameModule::Piece::Piece(std::string name)
	: Actor{ name }, posOnGrid{}, p_currentBlocks{ &upBlocks }
{
	init();
}

std::vector<Vector2i>& gameModule::Piece::getRefUpBlocks()
{
	return upBlocks;
}

std::vector<Vector2i>& gameModule::Piece::getRefRightBlocks()
{
	return leftBlocks;
}

std::vector<Vector2i>& gameModule::Piece::getRefDownBlocks()
{
	return downBlocks;
}

std::vector<Vector2i>& gameModule::Piece::getRefLeftBlocks()
{
	return rightBlocks;
}

gameModule::Piece::~Piece() {}

void gameModule::Piece::init()
{
	blocsColor = std::array<Color, 6>{
		RED, GREEN, DARKBLUE, VIOLET, GOLD, PINK} [rand() % 6] ;
}

void Piece::action(float delta) {}

void gameModule::Piece::render(float delta)
{
	auto currentBlocks = (*p_currentBlocks);
	for (size_t i = 0; i < currentBlocks.size(); ++i)
	{
		std::cout << posOnGrid.x << " " << posOnGrid.y << std::endl;
		DrawRectangle((currentBlocks[i].x + posOnGrid.x) * GameParams::getCellSizePx() + getX(),
			(currentBlocks[i].y  + posOnGrid.y) * GameParams::getCellSizePx() + getY(),
			GameParams::getCellSizePx(),
			GameParams::getCellSizePx(),
			blocsColor);
	}
}

void gameModule::Piece::rotateLeft()
{
	if (p_currentBlocks == &upBlocks) {
		p_currentBlocks = &leftBlocks;
	}
	else if (p_currentBlocks == &leftBlocks) {
		p_currentBlocks = &downBlocks;
	}
	else if (p_currentBlocks == &downBlocks) {
		p_currentBlocks = &rightBlocks;
	}
	else {
		p_currentBlocks = &upBlocks;
	}
}

void gameModule::Piece::rotateRight()
{
	if (p_currentBlocks == &upBlocks) {
		p_currentBlocks = &rightBlocks;
	}
	else if (p_currentBlocks == &leftBlocks) {
		p_currentBlocks = &upBlocks;
	}
	else if (p_currentBlocks == &downBlocks) {
		p_currentBlocks = &leftBlocks;
	}
	else {
		p_currentBlocks = &downBlocks;
	}
}

void gameModule::Piece::moveOnGrid(int x, int y)
{
	posOnGrid.x += x;
	posOnGrid.y += y;
}

void gameModule::Piece::setPosOnGrid(int x, int y)
{
	posOnGrid.x = x;
	posOnGrid.y = y;
}

Vector2i gameModule::Piece::getPosOnGrid()
{
	return posOnGrid;
}

std::vector<Vector2i>* gameModule::Piece::getBlocks()
{
	return p_currentBlocks;
}

std::vector<Vector2i> gameModule::Piece::getGlobalBlocksCoords()
{
	std::vector<Vector2i> coords;

	if (p_currentBlocks) {
		for (size_t i = 0; i < p_currentBlocks->size(); i++) {
			Vector2i localPieceCoords = p_currentBlocks->at(i);
			coords.push_back(Vector2i{ localPieceCoords.x + posOnGrid.x, localPieceCoords.y + posOnGrid.y });
		}
	}
	return coords;
}

Vector2i& gameModule::Vector2i::operator+(const Vector2i& other)
{
	x += other.x;
	y += other.y;
	return *this;
}

Vector2i& gameModule::Vector2i::operator+=(const Vector2i& other)
{
	x += other.x;
	y += other.y;
	return *this;
}

Vector2i& gameModule::Vector2i::operator+(int val)
{
	x += val;
	y += val;
	return *this;
}

Vector2i& gameModule::Vector2i::operator+=(int val)
{
	x += val;
	y += val;
	return *this;
}

Vector2i& gameModule::Vector2i::operator*(int val)
{
	x *= val;
	y *= val;
	return *this;
}

Vector2i& gameModule::Vector2i::operator*=(int val)
{
	x *= val;
	y *= val;
	return *this;
}
