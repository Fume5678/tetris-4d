#include "Actor.h"
#include "Root.h"

using namespace engineModule;
engineModule::Actor::Actor() : name{}, parent{}
{
	isActive = true;
}

Actor::Actor(std::string name) : name{ name }, parent{} {
	isActive = true;
}

void Actor::render(float delta) {}

void engineModule::Actor::action(float delta) {}

void Actor::onDestroy() {}

engineModule::Actor::~Actor() {}

void Actor::destroy() {
	onDestroy();

	while (!childs.empty()) {
		Actor* tmp = childs.back();
		tmp->destroy();
		childs.pop_back();
		delete tmp;
	}
}

void Actor::addChild(Actor* newChild) {
	if (newChild->name.empty()) {
		throw std::runtime_error{"Not set the name"};
	}


	for (auto& child : childs) {
		if (child == newChild) {
			std::cerr << "[WARNING]: child(" << newChild->getName() << "{"
				<< newChild << "}) already added to " << parent;
			return;
		}
	}

	newChild->setParent(this);
	childs.push_back(newChild);
}

void Actor::removeChild(Actor* child) {
	for (std::vector<Actor*>::iterator it = childs.begin(); it < childs.end();
		 ++it) {
		if (*it == child) {
			(*it)->setParent(nullptr);
			childs.erase(it);
			return;
		}
		std::cerr << "[WARNING]: child(" << child << "{" << child
			<< "}) not found for " << parent;
	}
}

Actor* Actor::find(std::string name) const {
	for (auto& child : childs) {
		if (child->getName() == name) {
			return child;
		}
	}
	return nullptr;
}

Actor* Actor::find(Actor* actor) const {
	for (auto& child : childs) {
		if (child == actor) {
			return child;
		}
	}
	return nullptr;
}

void engineModule::Actor::setParent(Actor* newParent) {
	if (parent == nullptr) {
		parent = newParent;
		return;
	}

	auto childs = this->parent->getChilds();
	for (std::vector<Actor*>::iterator it = childs.begin(); it < childs.end();
		 ++it) {
		if (*it == this) {
			childs.erase(it);
			break;
		}
	}
	parent = newParent;
}

void engineModule::Actor::setActive(bool val) {
	isActive = val;
}

void engineModule::Actor::setName(std::string val)
{
	name = val;
}

std::string engineModule::Actor::getName()
{
	return name;
}

bool engineModule::Actor::getActive() const {
	return isActive;
}

Actor* engineModule::Actor::getParent() const {
	return parent;
}

std::string Actor::getName() const {
	return name;
}

std::vector<Actor*>& engineModule::Actor::getChilds() {
	return childs;
}