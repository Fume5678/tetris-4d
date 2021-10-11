#include <raylib.h>

#include "engineModule/Actor.h"
#include "gameModule/Game.h"
#include "engineModule/EngineParams.h"
#include "engineModule/Root.h"
#include <thread>
#include <chrono>

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
		//std::chrono::steady_clock::time_point pr_StartTime = std::chrono::steady_clock::now();
		
		float delta = GetFrameTime();

		//std::thread tha{ mainActions, root, delta };
		mainActions(root, delta);

		BeginDrawing();
		ClearBackground(WHITE);
		
		//std::thread thr{ mainRender, root, delta };
		mainRender(root, delta);

		if (EngineParams::isShowFps()) {
			DrawFPS(5, 4);
		}

		//tha.join();
		//thr.join();
		//std::chrono::steady_clock::time_point pr_EndTime = std::chrono::steady_clock::now();
		//auto Duration = std::chrono::duration_cast<std::chrono::microseconds>(pr_EndTime - pr_StartTime);
		//std::cout << "Duration " << Duration.count() << " ms" << std::endl;
		
		EndDrawing();
	}

	CloseAudioDevice();

	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}