#include <SFML/Graphics.hpp>
#include "renderdemo.h"

void renderdemo(sf::RenderWindow& window, unsigned long frameNumber) {
    // Clear the window with a color
    window.clear(sf::Color(0, 20, 30));

    // Draw a green rectangle in the top left
    sf::RectangleShape rect;
    rect.setPosition(sf::Vector2f(0, 0));
    rect.setSize(sf::Vector2f(30, 30));
    rect.setFillColor(sf::Color(100, 250, 50));
    window.draw(rect);
    // Draw a red circle in the top right
    sf::CircleShape circ;
    circ.setPosition(sf::Vector2f(window.getSize().x - 30, 0));
    circ.setRadius(15);
    circ.setFillColor(sf::Color::Red);
    window.draw(circ);
    // Draw a funny circle
    sf::CircleShape circ2;
    circ2.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
    circ2.setRadius(30);
    circ2.setFillColor(sf::Color(
        (frameNumber * 3) % 250,
        (frameNumber * 2) % 250,
        (frameNumber) % 250
    ));
    window.draw(circ2);

    // Make a "minceraft" world
    int w[5][6] = {
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {1, 1, 0, 0, 0, 1},
        {2, 2, 1, 1, 1, 2},
        {2, 2, 2, 2, 2, 2}
    };
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 6; x++) {
            int b = w[y][x];
            sf::RectangleShape rect;
            rect.setPosition(sf::Vector2f((x + 4) * 30, y * 30));
            rect.setSize(sf::Vector2f(30, 30));
            if (b == 0) rect.setFillColor(sf::Color(91, 155, 186)); // Sky
            else if (b == 1) rect.setFillColor(sf::Color(0, 255, 0)); // Grass
            else if (b == 2) rect.setFillColor(sf::Color(105, 59, 36)); // Dirt
            window.draw(rect);
        }
    }

    // Display everything
    window.display();
}
