#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "assethandler.h"
#include "renderer.h"
#include "renderdata.h"
#include "worldstate.h"
#include "worldobject.h"
#include "worldobjects/redcube.h" // Debugging
#include "worldobjects/bluecube.h"
#include "worldobjects/stationaryimage.h"

// SFML Demo
int main() {
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "PlatScifi" };
    window.setFramerateLimit(144);

    // TODO: build not working on Linux?

    // Main data and objects
    AssetHandler assetHandler;
    Renderer renderer(window, assetHandler);
    WorldState worldState;
    // Debug: create a red cube, blue cube, and image
    worldState.spawnObject(new RedCube(0, 0));
    worldState.spawnObject(new BlueCube());
    worldState.spawnObject(new StationaryImage(6, 6, 2, 2, "assets/tiv_logo.png"));

    while (window.isOpen()) {
        for (auto event = sf::Event{}; window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Update the world
        worldState.update();

        // Render the world
        window.clear();
        renderer.renderWorld(worldState);
        window.display();
    }
}
