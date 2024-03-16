#include <SFML/Graphics.hpp>
#include <iostream>
#include "renderdata.h"
#include "worldobjects/redcube.h" // Debugging

// SFML Demo
int main() {
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "PlatScifi" };
    window.setFramerateLimit(144);

    // Data
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
        RenderData d = cub.getRenderData();
        std::cout << d.locx << ", " << d.locy << ", height: " << d.height << std::endl;
        sf::RectangleShape toRender;
        if (d.coordType == CoordType::Screen) {
            // Literal coordinates
            toRender.setSize(sf::Vector2f(d.width, d.height));
            toRender.setPosition(sf::Vector2f(d.locx, d.locy));
        } else {
            // Convert from world to screen coordinates
            // TODO: conversion (for testing, 30 pixels is one screen unit)
            toRender.setSize(sf::Vector2f(d.width * 30, d.height * 30));
            toRender.setPosition(sf::Vector2f(d.locx * 30, d.locy * 30));
        }
        toRender.setFillColor(sf::Color(d.color.r, d.color.g, d.color.b));
        window.draw(toRender);

        window.display();
    }
}
