#include "gameModule/GameParams.h"

#include "Game.h"


using namespace gameModule;

Game::Game(std::string name):Actor{name} {
	init();
}

gameModule::Game::~Game() {}

void Game::init() {
	bg = LoadTexture(ASSETS_PATH"background.png");
}

void gameModule::Game::action(float delta) {
	redRing.width = GameParams::getCellSizePx() * GameParams::getGridSize().first;
	redRing.height = GameParams::getCellSizePx() * GameParams::getGridSize().second;
	redRing.x = 0;
	redRing.y = 0;
}

void gameModule::Game::render(float delta) {
	DrawTexture(bg, 0, 0, WHITE);
	
	DrawRectangleLinesEx(redRing, 10, RED);
}
