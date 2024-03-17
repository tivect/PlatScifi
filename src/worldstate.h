#pragma once

#include <vector>
#include "worldobject.h"

// Store the full state of the world and all objects
class WorldState {
private:
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
    ~WorldState();
};
