#pragma once

#include <SFML/Graphics.hpp>
#include "worldstate.h"
#include "renderdata.h"

// Render the world
class Renderer {
private:
    sf::RenderWindow& window;

public:
    // Create the renderer
    Renderer(sf::RenderWindow& window);

    // Render from a RenderData object
    void renderFromData(RenderData& data);

    // Render the entire world
    void renderWorld(WorldState& worldState);
};
