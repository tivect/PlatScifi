#include "worldstate.h"

void WorldState::spawnObject(WorldObject* object) {
    objects.push_back(object);
}

void WorldState::update() {
    for (WorldObject* object : objects) {
        object->update();
    }
}

std::vector<WorldObject*>::iterator WorldState::objectsBegin() {
    return objects.begin();
}

std::vector<WorldObject*>::iterator WorldState::objectsEnd() {
    return objects.end();
}

void WorldState::clear() {
    while (!objects.empty()) {
        // TODO: good memory freeing?
        delete objects.back();
        objects.pop_back();
    }
}

WorldState::~WorldState() {
    clear();
}
