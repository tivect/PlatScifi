#include <SFML/Graphics.hpp>
#include "renderdemo.h"

void renderdemo(sf::RenderWindow& window) {
    // Create a rectangle
    sf::RectangleShape rect;
    rect.setPosition(sf::Vector2f(0, 0));
    rect.setSize(sf::Vector2f(22, 22));
    rect.setFillColor(sf::Color(100, 250, 50));
    window.draw(rect);
}
