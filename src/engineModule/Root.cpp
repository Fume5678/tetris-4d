#include "Root.h"

using namespace engineModule;

Root* Root::root{};

Root::Root(std::string name) : Actor{name} {}

engineModule::Root::~Root() {
    root->destroy();
}

Root* engineModule::Root::getRoot() {
    if (root) {
        return root;
    }

    Actor* tmp = new Root{"root"};
    root       = dynamic_cast<Root*>(tmp);
    return root;
}
