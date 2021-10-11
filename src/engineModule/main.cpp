#include <raylib.h>

#include "engineModule/Actor.h"
#include "gameModule/Game.h"
#include "engineModule/EngineParams.h"
#include "engineModule/Root.h"

using namespace engineModule;
using namespace gameModule;

void mainRender(Actor* actor, float delta) {
	if (!actor->getActive()) {
		return;
	}
	actor->render(delta);
	for (const auto& child : actor->getChilds()) {
		mainRender(child, delta);
	}
}

void mainActions(Actor* actor, float delta) {
	if (!actor->getActive()) {
		return;
	}
	actor->action(delta);
	for (const auto& child : actor->getChilds()) {
		mainActions(child, delta);
	}
}

int main(void) {
	// Initialization of game
	//--------------------------------------------------------------------------------------
	SetConfigFlags(FLAG_MSAA_4X_HINT);
	InitWindow(EngineParams::getScreenWidth(), EngineParams::getScreenHeight(), "tetris 4D ");
	InitAudioDevice();
	SetTargetFPS(EngineParams::getFps());

	// Initialization of object tree
	//--------------------------------------------------------------------------------------
	Root* root{ Root::getRoot() };
	Game game{ "game" };
	root->addChild(&game);

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Actions loop first
		float delta = GetFrameTime();
		mainActions(root, delta);

		// Render loop second
		BeginDrawing();
		ClearBackground(WHITE);

		mainRender(root, delta);
		if (EngineParams::isShowFps()) {
			DrawFPS(5, 4);
		}

		//----------------------------------------------------------------------------------
		EndDrawing();
	}

	CloseAudioDevice();

	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}