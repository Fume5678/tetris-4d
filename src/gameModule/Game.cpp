#include <thread>

#include "gameModule/GameParams.h"
#include "Game.h"
#include "gameModule/Piece.h"
#include "gameModule/PieceFactory.h"

using namespace gameModule;
using namespace engineModule;

Game::Game(std::string name):Actor{name}, gridTable{} {
	screenSize = ::EngineParams::getScreenResolution();
	EngineParams::setShowFps(true);

	// Starting blacksqare 
	for(size_t i = 11; i < 19; ++i){
		for(size_t j = 11; j < 19; ++j){
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

	activePiece = new Piece{"palka"};
	PieceFactory::buildFigure(activePiece, 'S');
	activePiece->setXY(blueRing.x, blueRing.y);
	addChild(activePiece);

}

void gameModule::Game::action(float delta) {
	redRing.width = GameParams::getCellSizePx() * 30; // 30 - red ring size
	redRing.height = GameParams::getCellSizePx() * 30;
	redRing.x = screenSize.first / 2 - redRing.width / 2;
	redRing.y = screenSize.second / 2 - redRing.height / 2;


	if(IsKeyDown(KEY_D)){
		// TODO: checking for collision
		activePiece->move(GameParams::getCellSizePx(), 0);
	}
	if(IsKeyDown(KEY_A)){
		activePiece->move(-GameParams::getCellSizePx(), 0);
	}
	if(IsKeyDown(KEY_W)){
		activePiece->move(0, -GameParams::getCellSizePx());
	}
	if(IsKeyDown(KEY_S)){
		activePiece->move(0, GameParams::getCellSizePx());
	}
	

	if(IsKeyPressed(KEY_Q)){
		activePiece->rotateLeft();
	}

	if(IsKeyPressed(KEY_E)){
		activePiece->rotateRight();
	}

	// TODO: checking for circle around earth 

}

void gameModule::Game::render(float delta) {
	DrawTexture(bg, 0, 0, WHITE);


	// TODO: optimize grid drawing
	for (int i = 0; i < 30; ++i) {
		for(int j = 0; j < 30; ++j){
			gridRect.x = i * GameParams::getCellSizePx() + redRing.x;
			gridRect.y = j * GameParams::getCellSizePx() + redRing.y;
			if(!gridTable[i][j]){
				DrawRectangleLinesEx(gridRect, 0.5, LIGHTGRAY);
			}else{
				if(10 < i && i < 19 && 10 <= j && j < 19){
					DrawRectangle(gridRect.x, gridRect.y, gridRect.width, gridRect.height, BLACK);
				}else {
					DrawRectangle(gridRect.x, gridRect.y, gridRect.width, gridRect.height, GRAY);
				}
			}
		}
	}

	DrawRectangleLinesEx(blueRing, 3, BLUE);
	DrawRectangleLinesEx(redRing, 3, RED);
	DrawRectangleLinesEx(redRing, 3, RED);
}
