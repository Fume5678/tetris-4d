#pragma once
#include <string>
#include "Actor.h"

namespace engineModule {

    class Root : public Actor {
        Root(std::string nodeName);

    public:
        ~Root();

        static Root* getRoot();

    private:
        static Root* root;
    };
} // namespace engineModule