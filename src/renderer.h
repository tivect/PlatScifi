#pragma once

#include <SFML/Graphics.hpp>
#include "gamestate.h"
#include "renderdata.h"
#include "assethandler.h"
#include "constants.h"

// Render the world
class Renderer {
private:
    sf::RenderWindow& window;
    AssetHandler& assetHandler;
    double worldCameraCenterX = 0;
    double worldCameraCenterY = 0;
    int screenPixPerWorld = 32;

public:
    // Create the renderer
    Renderer(sf::RenderWindow& window, AssetHandler& assetHandler);

    // Render from a RenderData object
    void renderFromData(RenderData data);

    // Set the camera
    void setCamera(double newWorldCameraCenterX, double newWorldCameraCenterY, double percentEasing = 0.0);

    // Render the entire world
    void renderWorldObjects(GameState& worldState);
};
