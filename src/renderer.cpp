#include <SFML/Graphics.hpp>
#include "renderer.h"

Renderer::Renderer(sf::RenderWindow& window) : window(window) { }

void Renderer::renderFromData(RenderData& data) {
    sf::RectangleShape toRender;
    if (data.coordType == CoordType::Screen) {
        // Literal coordinates
        toRender.setSize(sf::Vector2f(data.width, data.height));
        toRender.setPosition(sf::Vector2f(data.locx, data.locy));
    } else {
        // Convert from world to screen coordinates
        // TODO: conversion (for testing, 30 pixels is one screen unit)
        // TODO: render from the center position?
        toRender.setSize(sf::Vector2f(data.width * 30, data.height * 30));
        toRender.setPosition(sf::Vector2f(data.locx * 30, data.locy * 30));
    }
    toRender.setFillColor(sf::Color(data.color.r, data.color.g, data.color.b));
    window.draw(toRender);
}

void Renderer::renderWorld(WorldState& worldState) {
    for (auto it = worldState.objectsBegin(); it != worldState.objectsEnd(); it++) {
        renderFromData((*it)->getRenderData());
    }
    // todo: impl
}
