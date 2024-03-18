#include <SFML/Graphics.hpp>
#include "renderer.h"

Renderer::Renderer(sf::RenderWindow& window) : window(window) { }

void Renderer::renderFromData(RenderData& data) {
    // TODO: implement other types (like images)
    if (data.type == RenderType::Rectangle) {
        // Rectangle
        sf::RectangleShape toRender;
        if (data.coordType == CoordType::Screen) {
            // Literal coordinates
            toRender.setSize(sf::Vector2f(data.width, data.height));
            toRender.setPosition(sf::Vector2f(data.locx, data.locy));
        } else {
            // Convert from world to screen coordinates
            // TODO: conversion (for testing, 30 pixels is one world unit)
            // TODO: render from the center position?
            toRender.setSize(sf::Vector2f(data.width * 30, data.height * 30));
            toRender.setPosition(sf::Vector2f(data.locx * 30, data.locy * 30));
        }
        toRender.setFillColor(sf::Color(data.color.r, data.color.g, data.color.b));
        window.draw(toRender);
    } else if (data.type == RenderType::Circle) {
        // Circle
        sf::CircleShape toRender;
        if (data.coordType == CoordType::Screen) {
            // Literal coordinates
            toRender.setRadius((data.width + data.height) / 4);
            toRender.setPosition(sf::Vector2f(data.locx, data.locy));
        } else {
            // Convert from world to screen coordinates
            // TODO: conversion (for testing, 30 pixels is one world unit)
            // TODO: render from the center position?
            toRender.setRadius((data.width + data.height) / 4 * 30);
            toRender.setPosition(sf::Vector2f(data.locx * 30, data.locy * 30));
        }
        toRender.setFillColor(sf::Color(data.color.r, data.color.g, data.color.b));
        window.draw(toRender);
    } else {
        // Image
        // Load the image source file
        // TODO: refactor loading the image source to an ImageHandler class
        // TODO: with a hashmap that provides the image or loads it
        sf::Image img;
        if (!img.loadFromFile(data.imageSource)) {
            // Error
            // TODO: handle
            return;
        }
        sf::Texture tex;
        sf::Sprite toRender;
        if (data.coordType == CoordType::Screen) {
            // Literal coordinates
            tex.create(data.width, data.height);
            tex.update(img);
            toRender.setTexture(tex);
            toRender.setPosition(data.locx, data.locy);
        } else {
            // Convert from world to screen coordinates
            // TODO: conversion (for testing, 30 pixels is one world unit)
            // TODO: render from the center position?
            tex.create(data.width * 30, data.height * 30);
            tex.update(img);
            toRender.setTexture(tex);
            toRender.setPosition(data.locx * 30, data.locy * 30);
        }
        window.draw(toRender);
    }
}

void Renderer::renderWorld(WorldState& worldState) {
    for (auto it = worldState.objectsBegin(); it != worldState.objectsEnd(); it++) {
        renderFromData((*it)->getRenderData());
    }
    // todo: impl
}
