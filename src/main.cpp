#include <SFML/Graphics.hpp>
#include "renderdemo.h"

// SFML Demo
int main() {
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "PlatScifi" };
    window.setFramerateLimit(144);

    while (window.isOpen()) {
        // Handle events
        for (auto event = sf::Event{}; window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Render
        window.clear(sf::Color(0, 20, 30));

        // Use the demo
        renderdemo(window);
        
        window.display();
    }
}
