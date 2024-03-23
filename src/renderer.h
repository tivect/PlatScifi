#pragma once

#include <SFML/Graphics.hpp>
#include "gamestate.h"
#include "renderdata.h"
#include "assethandler.h"

// Render the world
class Renderer {
private:
    sf::RenderWindow& window;
    AssetHandler& assetHandler;

public:
    // Create the renderer
    Renderer(sf::RenderWindow& window, AssetHandler& assetHandler);

    // Render from a RenderData object
    void renderFromData(RenderData& data);

    // Render the entire world
    void renderWorldObjects(GameState& worldState);
};
