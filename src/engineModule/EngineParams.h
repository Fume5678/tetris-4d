#pragma once

#include <iostream>
#include <raylib.h>

namespace engineModule {
	class EngineParams {
		EngineParams();
		EngineParams(const EngineParams&) = delete;
	public:

		static void setShowFps(bool val);

		static bool isShowFps();

		static int getScreenWidth();

		static int getScreenHeight();

		static std::pair<int, int> getScreenResolution();

		static int getFps();

	private:
		static std::pair<int, int> screenResolution;
		static int fps;
		static bool bShowFps;
	};
}