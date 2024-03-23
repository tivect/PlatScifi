#include "gamestate.h"

void GameState::spawnObject(WorldObject* object) {
    objects.push_back(object);
}

void GameState::update() {
    for (WorldObject* object : objects) {
        object->update(worldState, objects);
    }
}

std::vector<WorldObject*>::iterator GameState::objectsBegin() {
    return objects.begin();
}

std::vector<WorldObject*>::iterator GameState::objectsEnd() {
    return objects.end();
}

void GameState::clear() {
    while (!objects.empty()) {
        // TODO: good memory freeing?
        delete objects.back();
        objects.pop_back();
    }
}

GameState::~GameState() {
    clear();
}
