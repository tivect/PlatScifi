#pragma once

#include <vector>
#include "worldobject.h"
#include "worldstate.h"

// Store the full state of the world and all objects
class GameState {
private:
    WorldState worldState;
    std::string levelName;
    std::string nextLevelName;
    std::vector<WorldObject*> objects;

public:
    // Spawn an object
    void spawnObject(WorldObject* object);
    // Update
    UpdateResult update();
    // Get the current level name
    std::string getLevelName();
    // Get the next level name
    std::string getNextLevelName();
    // Update the current level name
    void updateLevelNames(std::string newLevelName, std::string newNextLevelName); 
    // Get all objects
    std::vector<WorldObject*>::iterator objectsBegin();
    std::vector<WorldObject*>::iterator objectsEnd();
    // Clear all objects from the world, aside from Persisting objects
    void clear();
    // Destructor to free memory
    ~GameState();
};
