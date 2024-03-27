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
    void spawnWorld(GameState& gameState, std::string worldfile) {
        // Load the file
        // todo: error handling
        std::ifstream file(worldfile);
        std::string line;
        while (std::getline(file, line)) {
            // Parse line
            std::vector<std::string> parsed;
            std::string thisitem = "";
            for (char c : line) {
                if (c == ',') {
                    parsed.push_back(thisitem);
                    thisitem = "";
                } else if (c != ' ' && c != '\n') {
                    thisitem += c;
                }
            }
            if (thisitem != "") parsed.push_back(thisitem);
            // Process arguments
            // todo: error handling with try catch
            if (parsed[0].rfind("//", 0) == 0) {
                // Comment: skip
            } else if (parsed[0] == "StaticCollider") {
                gameState.spawnObject(new StaticCollider(
                    std::stoi(parsed[1]), std::stoi(parsed[2]), std::stoi(parsed[3]), std::stoi(parsed[4])
                ));
            } else if (parsed[0] == "Spike") {
                gameState.spawnObject(new Spike(
                    std::stoi(parsed[1]), std::stoi(parsed[2])
                ));
            } else if (parsed[0] == "StaticDeadly") {
		gameState.spawnObject(new StaticDeadly(
                    std::stoi(parsed[1]), std::stoi(parsed[2]), std::stoi(parsed[3]), std::stoi(parsed[4])
                ));
	    }
        }
    }
};
