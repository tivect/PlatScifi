#pragma once

#include <SFML/Graphics.hpp>
#include "renderdata.h"

// Render the world
class Renderer {
public:
    // Render from a RenderData object
    void renderFromData(sf::RenderWindow& window, RenderData& data);

    // Render the entire world
    void renderWorld(sf::RenderWindow& window/*, WorldState& worldState*/);
};
