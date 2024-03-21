#include <SFML/Graphics.hpp>
#include <iostream>
#include <set>
#include "assethandler.h"
#include "renderer.h"
#include "renderdata.h"
#include "worldstate.h"
#include "worldobject.h"
#include "worldobjects/redcube.h" // Debugging
#include "worldobjects/bluecube.h"
#include "worldobjects/stationaryimage.h"
#include "worldobjects/player.h"

// SFML Demo
int main() {
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "PlatScifi" };
    window.setFramerateLimit(144);

    // TODO: build not working on Linux?

    // Main data and objects
    AssetHandler assetHandler;
    Renderer renderer(window, assetHandler);
    WorldState worldState;
    std::set<sf::Keyboard::Key> keysPressed;

    // Main world objects
    Player* player = new Player(4, 10);
    worldState.spawnObject(player);

    // Debug: create a red cube, blue cube, and image
    worldState.spawnObject(new RedCube(0, 0));
    worldState.spawnObject(new BlueCube(0, 0));
    worldState.spawnObject(new StationaryImage(6, 6, 2, 2, "assets/tiv_logo.png"));

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
            player->move(-0.2, 0);
        }
        if (keysPressed.find(sf::Keyboard::D) != keysPressed.end()) {
            player->move(0.2, 0);
        }
        if (keysPressed.find(sf::Keyboard::W) != keysPressed.end()) {
            player->move(0, -0.2);
        }
        if (keysPressed.find(sf::Keyboard::S) != keysPressed.end()) {
            player->move(0, 0.2);
        }
        if (keysPressed.find(sf::Keyboard::Space) != keysPressed.end()) {
            worldState.spawnObject(new BlueCube(player->getLocx(), player->getLocy()));
            keysPressed.erase(sf::Keyboard::Space);
        }

        // Update the world
        worldState.update();

        // Render the world
        window.clear();
        renderer.renderWorld(worldState);
        window.display();
    }
}
