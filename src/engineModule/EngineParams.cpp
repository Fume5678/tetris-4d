#include "EngineParams.h"

using namespace engineModule;

bool EngineParams::bShowFps{};
int EngineParams::fps{ 60 };
std::pair<int, int> EngineParams::screenResolution{ 1280, 720 };

void EngineParams::setShowFps(bool val) {
	bShowFps = val;
}

bool EngineParams::isShowFps() {
	return bShowFps;
}

int EngineParams::getScreenWidth() {
	return screenResolution.first;
}

int EngineParams::getScreenHeight() {
	return screenResolution.second;
}

std::pair<int, int> EngineParams::getScreenResolution() {
	return screenResolution;
}

int EngineParams::getFps() {
	return fps;
}