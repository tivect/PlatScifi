#include "gamestate.h"

void GameState::spawnObject(WorldObject* object) {
    objects.push_back(object);
}

UpdateResult GameState::update() {
    for (WorldObject* object : objects) {
        UpdateResult updateResult = object->update(worldState, objects);
        if (updateResult == UpdateResult::NextLevel) {
            // TODO: improve this
            return UpdateResult::NextLevel;
        }
    }
    return UpdateResult::None;
}

std::string GameState::getLevelName() {
    return levelName;
}

std::string GameState::getNextLevelName() {
    return nextLevelName;
}

void GameState::updateLevelNames(std::string newLevelName, std::string newNextLevelName) {
    levelName = newLevelName;
    nextLevelName = newNextLevelName;
}

std::vector<WorldObject*>::iterator GameState::objectsBegin() {
    return objects.begin();
}

std::vector<WorldObject*>::iterator GameState::objectsEnd() {
    return objects.end();
}

void GameState::clear() {
    auto it = objects.begin();
    while (it != objects.end()) {
        if ((*it)->hasAttribute(ObjectAttribute::Persist)) {
            // Do not delete
            it++;
        } else {
            // TODO: good memory freeing?
            delete *it;
            it = objects.erase(it);
        }
    }
}

GameState::~GameState() {
    clear();
}
