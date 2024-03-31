#include "worldspawner.h"

void WorldSpawner::spawnWorld(GameState& gameState, std::string levelName) {
    // Load the file based on the level name
    // todo: error handling
    std::ifstream file("assets/" + levelName + ".csv");
    std::string line;
    std::string newNextLevelName = "level_0";
    // Clear the world
    gameState.clear();
    // Update
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
            newNextLevelName = parsed[1];
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
        } else if (parsed[0] == "LevelTp") {
            gameState.spawnObject(new LevelTp(
                std::stoi(parsed[1]), std::stoi(parsed[2])
            ));
        }
    }
    // Successful load: update the game state
    gameState.updateLevelNames(levelName, newNextLevelName);
}
