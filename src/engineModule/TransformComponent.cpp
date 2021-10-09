#include "TransformComponent.h"
#include "engineModule/TransformComponent.h"

using namespace engineModule;

void TransformComponent::setX(float val) {
    pos.first = val;
}

void TransformComponent::setY(float val) {
    pos.second = val;
}

void TransformComponent::setXY(float val1, float val2) {
    pos.first = val1;
    pos.second = val2;
}

void TransformComponent::setScaleX(float val) {
    scale.first = val;
}

void TransformComponent::setScaleY(float val) {
    scale.second = val;
}

void TransformComponent::setSizeX(float val) {
    size.first = val;
}

void TransformComponent::setSizeY(float val) {
    size.second = val;
}

float TransformComponent::getX() {
    return pos.first;
}

float TransformComponent::getY() {
    return pos.second;
}

float TransformComponent::getScaleX() {
    return scale.first;
}

float TransformComponent::getScaleY() {
    return scale.second;
}

float TransformComponent::getSizeX() {
    return size.first;
}

float TransformComponent::getSizeY() {
    return size.second;
}

std::pair<float, float> TransformComponent::getPos() const {
    return pos;
}

std::pair<float, float> TransformComponent::getScale() const {
    return scale;
}

std::pair<float, float> TransformComponent::getSize() const {
    return size;
}
