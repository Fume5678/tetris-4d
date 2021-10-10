#include <sstream>
#include <array>

#include "gameModule/GameParams.h"
#include "Game.h"
#include "gameModule/Piece.h"
#include "gameModule/PieceFactory.h"

#define MOVE_DELAY 3
#define REDRING_DELAY 25

using namespace gameModule;
using namespace engineModule;

Game::Game(std::string name) :Actor{ name }, gridTable{}, currentTick{} {
	screenSize = ::EngineParams::getScreenResolution();
	EngineParams::setShowFps(true);

	// Starting blacksqare 
	for (size_t i = 11; i < 19; ++i) {
		for (size_t j = 11; j < 19; ++j) {
			gridTable[i][j] = true;
		}
	}

	init();
}

gameModule::Game::~Game() {}

void Game::init() {
	bg = LoadTexture(ASSETS_PATH"background.png");
	bg.width = ::EngineParams::getScreenWidth();
	bg.height = ::EngineParams::getScreenHeight();

	gridRect.width = GameParams::getCellSizePx();
	gridRect.height = GameParams::getCellSizePx();

	// Blue ring
	blueRing.width = GameParams::getCellSizePx() * 24; // 24 - blue ring size;
	blueRing.height = GameParams::getCellSizePx() * 24;
	blueRing.x = screenSize.first / 2 - blueRing.width / 2;
	blueRing.y = screenSize.second / 2 - blueRing.height / 2;

	redRing.width = GameParams::getCellSizePx() * 30; // 30 - red ring size
	redRing.height = GameParams::getCellSizePx() * 30;
	redRing.x = screenSize.first / 2 - redRing.width / 2;
	redRing.y = screenSize.second / 2 - redRing.height / 2;

	setX(redRing.x);
	setY(redRing.y);

	activePiece = new Piece;
	PieceFactory::buildFigure(activePiece, 'S');
	activePiece->setName("Piece");
	activePiece->setXY(redRing.x, redRing.y);
	activePiece->setPosOnGrid(3, 3);
	addChild(activePiece);

}

void gameModule::Game::action(float delta) {
	currentTick++;
	movePiece();

	// RedRing
	if (currentTick % REDRING_DELAY == 0) {
		redRing.x += GameParams::getCellSizePx();
		redRing.y += GameParams::getCellSizePx();
		redRing.width -= GameParams::getCellSizePx() * 2;
		redRing.height -= GameParams::getCellSizePx() * 2;
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
			}
			else {
				if (11 <= i && i < 19 && 11 <= j && j < 19) {
					DrawRectangle(gridRect.x, gridRect.y, gridRect.width, gridRect.height, BLACK);
				}
				else {
					DrawRectangle(gridRect.x, gridRect.y, gridRect.width, gridRect.height, GRAY);

				}
			}

		}
	}

	DrawRectangleLinesEx(blueRing, 3, BLUE);
	DrawRectangleLinesEx(redRing, 3, RED);
	DrawRectangleLinesEx(redRing, 3, RED);
}


void Game::destroyPiece(){
	if (!activePiece) {
		return;
	}

	auto coords = activePiece->getGlobalBlocksCoords();
	for (const auto& crd : coords) {
		gridTable[crd.x][crd.y] = true;
	}

	removeChild(activePiece);
	delete activePiece;
	activePiece = nullptr;

	// Reset red ring
	redRing.width = GameParams::getCellSizePx() * 30; // 30 - red ring size
	redRing.height = GameParams::getCellSizePx() * 30;
	redRing.x = screenSize.first / 2 - redRing.width / 2;
	redRing.y = screenSize.second / 2 - redRing.height / 2;
}

void gameModule::Game::spawnPiece()
{
	if (activePiece) {
		TraceLog(LOG_ERROR, "Piece already create");
	}

	char shape = std::array<char, 2>{
		'I', 'S'} [rand() % 2] ;

	activePiece = new Piece;
	std::stringstream sstr;
	sstr << "Piece_" << activePiece;
	activePiece->setName(sstr.str());
	addChild(activePiece);
}

void Game::movePiece()
{
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

bool gameModule::Game::isCollide(int directX, int directY)
{
	if (!activePiece) {
		return false;
	}

	std::vector<Vector2i> pieceBlocksCoord = activePiece->getGlobalBlocksCoords();
	for (const auto& coord : pieceBlocksCoord) {
		if (gridTable[coord.x + directX][coord.y + directY]) {
			return true;
		}
	}

	return false;

}
