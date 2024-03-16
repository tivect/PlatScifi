#include <SFML/Graphics.hpp>
#include <iostream>
#include "renderer.h"
#include "renderdata.h"
#include "worldobjects/redcube.h" // Debugging

// SFML Demo
int main() {
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "PlatScifi" };
    window.setFramerateLimit(144);

    // Main data and objects
    Renderer renderer;
    // Debug: create a red cube
    RedCube cub;

    while (window.isOpen()) {
        for (auto event = sf::Event{}; window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();

        // Debug: update and render the red cube
        cub.update();
        renderer.renderFromData(window, cub.getRenderData());

        window.display();
    }
}
