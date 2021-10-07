#include "gameModule/GameParams.h"

#include "Game.h"


using namespace gameModule;
using namespace engineModule;

Game::Game(std::string name):Actor{name} {
	screenSize = ::EngineParams::getScreenResolution();
	EngineParams::setShowFps(true);
	
	init();
}

gameModule::Game::~Game() {}

void Game::init() {
	bg = LoadTexture(ASSETS_PATH"background.png");
	bg.width = ::EngineParams::getScreenWidth();
	bg.height = ::EngineParams::getScreenHeight();

	gridRect.width = GameParams::getCellSizePx();
	gridRect.height = GameParams::getCellSizePx();
}

void gameModule::Game::action(float delta) {
	redRing.width = GameParams::getCellSizePx() * 30; // 30 - red ring size
	redRing.height = GameParams::getCellSizePx() * 30;
	redRing.x = screenSize.first / 2 - redRing.width / 2;
	redRing.y = screenSize.second / 2 - redRing.height / 2;

	blueRing.width = GameParams::getCellSizePx() * 24; // 24 - blue ring size;
	blueRing.height = GameParams::getCellSizePx() * 24;
	blueRing.x = screenSize.first / 2 - blueRing.width / 2;
	blueRing.y = screenSize.second / 2 - blueRing.height / 2;

	blackSquare.width = GameParams::getCellSizePx() * 8; // 8 - black square size
	blackSquare.height = GameParams::getCellSizePx() * 8; 
	blackSquare.x = screenSize.first / 2 - blackSquare.width / 2;
	blackSquare.y = screenSize.second / 2 - blackSquare.height / 2;

}

void gameModule::Game::render(float delta) {
	DrawTexture(bg, 0, 0, WHITE);
	
	// —генерировать текстуру, а не выводить циклами
	for (int i = 0; i < 30; ++i) {
		for(int j = 0; j < 30; ++j){
			gridRect.x = i * GameParams::getCellSizePx() + redRing.x;
			gridRect.y = j * GameParams::getCellSizePx() + redRing.y;
			DrawRectangleLinesEx(gridRect, 0.5, LIGHTGRAY);
		}
	}

	DrawRectangleLinesEx(blueRing, 3, BLUE);
	DrawRectangleLinesEx(redRing, 3, RED);
	DrawRectangleLinesEx(redRing, 3, RED);
	DrawRectangleRec(blackSquare, BLACK);
}
