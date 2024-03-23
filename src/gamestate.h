#pragma once

#include <vector>
#include "worldobject.h"
#include "worldstate.h"

// Store the full state of the world and all objects
class GameState {
private:
    WorldState worldState;
    std::vector<WorldObject*> objects;

public:
    // Spawn an object
    void spawnObject(WorldObject* object);
    // Update
    void update();
    // Get all objects
    std::vector<WorldObject*>::iterator objectsBegin();
    std::vector<WorldObject*>::iterator objectsEnd();
    // Clear all items
    void clear();
    // Destructor to free memory
    ~GameState();
};
