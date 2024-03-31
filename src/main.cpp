#include <SFML/Graphics.hpp>
#include <iostream>
#include <set>
#include "assethandler.h"
#include "renderer.h"
#include "renderdata.h"
#include "gamestate.h"
#include "worldspawner.h"
#include "worldobject.h"
#include "worldobjectincludes.h"

// SFML Demo
int main() {
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "PlatScifi" };
    window.setFramerateLimit(144);

    // TODO: build not working on Linux?

    // Main data and objects
    AssetHandler assetHandler;
    Renderer renderer(window, assetHandler);
    GameState gameState;
    WorldSpawner worldSpawner;
    std::set<sf::Keyboard::Key> keysPressed;

    // Main world objects
    Player* player = new Player(5, 10);
    gameState.spawnObject(player);

    // Debug: load a basic level from a txt file
    worldSpawner.spawnWorld(gameState, "level_0");
    /*// Example level (level_0.csv)
    // Bottom colliders
    gameState.spawnObject(new StaticCollider(3, 25, 6, 2));
    gameState.spawnObject(new StaticCollider(9, 27, 10, 2));
    gameState.spawnObject(new StaticCollider(19, 25, 6, 2));
    // Vertical colliders
    gameState.spawnObject(new StaticCollider(0, 0, 2, 25));
    gameState.spawnObject(new StaticCollider(25, 0, 2, 19));
    // Extra blocks
    gameState.spawnObject(new StaticCollider(23, 29, 44, 19));
    // Spike
    gameState.spawnObject(new Spike(28, 28));*/

    // Main game loop
    while (window.isOpen()) {
        // Poll events
        for (auto event = sf::Event{}; window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                // Close window
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                keysPressed.insert(event.key.code);
            } else if (event.type == sf::Event::KeyReleased) {
                keysPressed.erase(event.key.code);
            }
        }

        // Use input
        if (keysPressed.find(sf::Keyboard::A) != keysPressed.end()) {
            player->accelerate(-0.05, 0);
        }
        if (keysPressed.find(sf::Keyboard::D) != keysPressed.end()) {
            player->accelerate(0.05, 0);
        }
        if (
            keysPressed.find(sf::Keyboard::W) != keysPressed.end()
            || keysPressed.find(sf::Keyboard::Space) != keysPressed.end()
        ) {
            player->jump();
        }
        if (keysPressed.find(sf::Keyboard::S) != keysPressed.end()) {
            player->accelerate(0, 0.05);
        }
        if (keysPressed.find(sf::Keyboard::R) != keysPressed.end()) {
            // Restart to spawn location
            player->teleport(5.0, 10.0);
        }
        if (keysPressed.find(sf::Keyboard::P) != keysPressed.end()) {
            // Debug: spawn blue cubes
            gameState.spawnObject(new BlueCube(player->getLocx(), player->getLocy()));
            keysPressed.erase(sf::Keyboard::P);
        }

        // Update the game and world
        UpdateResult updateResult = gameState.update();
        if (updateResult == UpdateResult::NextLevel) {
            // Load the next level, if possible
            // TODO: impl better
            worldSpawner.spawnWorld(gameState, gameState.getNextLevelName());
        }

        // Render the game and world
        window.clear(sf::Color(111, 201, 252));
        renderer.setCamera(player->getLocx(), player->getLocy(), 0.8);
        renderer.renderWorldObjects(gameState);
        window.display();
    }
}
