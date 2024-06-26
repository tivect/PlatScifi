#include "gamestate.h"

void GameState::spawnObject(WorldObject* object) {
    objects.push_back(object);
}

UpdateResult GameState::update() {
    // Update the collision matrix with every world object
    collisionMatrix.clear();
    for (WorldObject* object : objects) {
        collisionMatrix.addObject(object);
    }

    // Update world objects
    std::vector<WorldObject*> newToSpawn;
    for (std::vector<WorldObject*>::iterator it = objects.begin(); it != objects.end();) {
        UpdateResult updateResult = (*it)->update(*this);
        if (updateResult == UpdateResult::NextLevel) {
            // TODO: improve this
            return UpdateResult::NextLevel;
        } else if (updateResult == UpdateResult::DieReset) {
            // Player died
            return UpdateResult::DieReset;
        } else if (updateResult == UpdateResult::ReplicateAndDestroy) {
            // Replicate it (spawn two replicators)
            Animal* animal1 = new Animal(
                "replicator", (*it)->getLocx(), (*it)->getLocy()
            );
            animal1->teleport(animal1->getLocx() - 1.5, animal1->getLocy()); // -0.7
            animal1->setDimensions((*it)->getWidth() * 0.8, (*it)->getHeight() * 0.8);
            newToSpawn.push_back(animal1);
            Animal* animal2 = new Animal(
                "replicator", (*it)->getLocx(), (*it)->getLocy()
            );
            animal2->teleport(animal2->getLocx() + 1.5, animal2->getLocy());
            animal2->setDimensions((*it)->getWidth() * 0.8, (*it)->getHeight() * 0.8);
            animal2->reverseDirection();
            newToSpawn.push_back(animal2);
            // Destroy the previous enemy
            it = objects.erase(it);
        } else {
            // Move on
            it++;
        }
    }
    for (WorldObject* newObject : newToSpawn) objects.push_back(newObject);
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

WorldState& GameState::getWorldState() {
    return worldState;
}

WorldCollisionMatrix& GameState::getCollisionMatrix() {
    return collisionMatrix;
}

void GameState::updateLevelNames(std::string newLevelName, std::string newNextLevelName) {
    levelName = newLevelName;
    nextLevelName = newNextLevelName;
    // Add the message
    // TODO: use level display names
    addUIMessage("Teleported to " + newLevelName, { 0, 160, 0 });
}

void GameState::addUIMessage(std::string message, Color color, int fontSize, long durationFrames, bool debug) {
    // TODO: do not add debug messages in a release build
    uiMessages.push_back({
        message,
        color,
        fontSize,
        durationFrames
    });
    if (uiMessages.size() > 5) uiMessages.erase(uiMessages.begin());
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
