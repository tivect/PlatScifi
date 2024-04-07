#include "gamestate.h"

void GameState::spawnObject(WorldObject* object) {
    objects.push_back(object);
}

UpdateResult GameState::update() {
    // Update world objects
    for (WorldObject* object : objects) {
        UpdateResult updateResult = object->update(worldState, objects);
        if (updateResult == UpdateResult::NextLevel) {
            // TODO: improve this
            return UpdateResult::NextLevel;
        } else if (updateResult == UpdateResult::DieReset) {
            // Died
            return UpdateResult::DieReset;
        }
    }
    // Update UI messages
    for (std::vector<UIMessage>::iterator it = uiMessages.begin(); it != uiMessages.end();) {
        if (it->update()) {
            // Delete the message
            it = uiMessages.erase(it);
        } else {
            it++;
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
    // Add the message
    // TODO: use level display names
    addUIMessage("Teleported to " + newLevelName, { 255, 255, 255 });
}

void GameState::addUIMessage(std::string message, Color color, int fontSize, long durationFrames) {
    uiMessages.push_back({
        message,
        color,
        fontSize,
        durationFrames
    });
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
