#pragma once
#include <vector>
#include <string>
#include <raylib.h>
#include "engineModule/Actor.h"

namespace gameModule {
    class Game : public engineModule::Actor{
    public:
        Game(std::string name);
        ~Game();

        void init();

        void action(float delta) override;
        void render(float delta) override;


    private:
        std::pair<float, float> screenSize;
        Texture2D bg;
        int stepTimer;
        int deleyRedRing;
        Rectangle redRing;
        Rectangle blueRing;
        Rectangle gridRect;
        Rectangle blackSquare;
    };
} // namespace gameModule