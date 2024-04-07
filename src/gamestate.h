#pragma once

#include <vector>
#include "worldobject.h"
#include "worldstate.h"
#include "uimessage.h"

// Store the full state of the world and all objects
class GameState {
private:
    WorldState worldState;
    std::string levelName;
    std::string nextLevelName;

public:
    // All world objects (public)
    std::vector<WorldObject*> objects;
    // All UI messages (public)
    std::vector<UIMessage> uiMessages;

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
    // Add a UI message
    void addUIMessage(std::string message, Color color, int fontSize = 14, long durationFrames = 150);
    // Clear all objects from the world, aside from Persisting objects
    void clear();
    // Destructor to free memory
    ~GameState();
};
