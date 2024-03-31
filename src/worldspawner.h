#pragma once

#include <string>
#include <fstream>
#include <vector>
#include "gamestate.h"
#include "worldobjectincludes.h"

// Spawn the world from a formatted text file
class WorldSpawner {
public:
    // Spawn given the game state and a .csv file (comments supported)
    /* Example:
        // Bottom colliders
        StaticCollider, 3, 25, 6, 2
        StaticCollider, 9, 27, 10, 2
        StaticCollider, 19, 25, 6, 2
    */
    void spawnWorld(GameState& gameState, std::string levelName); 
};
