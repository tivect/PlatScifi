#include "worldspawner.h"

void WorldSpawner::spawnWorld(GameState& gameState, std::string levelName) {
    // Load the file based on the level name
    // todo: error handling
    std::ifstream file;
    std::string line;
    std::string newNextLevelName = "level_0";
    try {
        file.open("assets/" + levelName + ".csv");
    } catch (std::exception& e) {
        // Failed
        return;
    }
    // Clear the world
    gameState.clear();
    // Try to update the world
    try {
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
            } else if (parsed[0] == "nextLevelName") {
                if (parsed.size() < 2) throw;
                newNextLevelName = parsed[1];
            } else if (parsed[0] == "StaticCollider") {
                if (parsed.size() < 5) throw;
                gameState.spawnObject(new StaticCollider(
                    std::stoi(parsed[1]), std::stoi(parsed[2]), std::stoi(parsed[3]), std::stoi(parsed[4])
                ));
            } else if (parsed[0] == "Spike") {
                if (parsed.size() < 3) throw;
                gameState.spawnObject(new Spike(
                    std::stoi(parsed[1]), std::stoi(parsed[2])
                ));
            } else if (parsed[0] == "StaticDeadly") {
                if (parsed.size() < 5) throw;
                gameState.spawnObject(new StaticDeadly(
                    std::stoi(parsed[1]), std::stoi(parsed[2]), std::stoi(parsed[3]), std::stoi(parsed[4])
                ));
            } else if (parsed[0] == "LevelTp") {
                if (parsed.size() < 3) throw;
                gameState.spawnObject(new LevelTp(
                    std::stoi(parsed[1]), std::stoi(parsed[2])
                ));
            } else if (parsed[0] == "MovingCollider") {
                if (parsed.size() < 8) throw;
                gameState.spawnObject(new MovingCollider(
                    std::stoi(parsed[1]), std::stoi(parsed[2]), std::stoi(parsed[3]),
                    std::stoi(parsed[4]), std::stol(parsed[5]), std::stoi(parsed[6]),
                    std::stoi(parsed[7])
                ));
            }
        }
    } catch (std::exception& e) {
        // Failed: re-clear the world
        gameState.clear();
        return;
    }
    // Successful load: update the game state
    gameState.updateLevelNames(levelName, newNextLevelName);
}
