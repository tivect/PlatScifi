#include <SFML/Graphics.hpp>
#include "renderdemo.h"

// SFML Demo
int main() {
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "PlatScifi" };
    window.setFramerateLimit(144);

    unsigned long frameNumber = 0;

    while (window.isOpen()) {
        // Handle events
        for (auto event = sf::Event{}; window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Render using the demo
        renderdemo(window, frameNumber);

        // Increase the frame count
        frameNumber++;
    }
}
