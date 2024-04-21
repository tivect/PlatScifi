#pragma once

#include "../worldobject.h"

// Stores a stationary image at a point in space
class Spike : public WorldObject {
private:
    // Frame oscillations
    long frameCount = 0;

public:
    // Constructor: provide the name of the asset from assets (ex. "assets/tiv_logo.png")
    Spike(double spawnx, double spawny) : WorldObject() {
        locx = spawnx;
        locy = spawny;
        this->width = 1;
        this->height = 1;
        objectAttributes.insert(ObjectAttribute::Collision);
        objectAttributes.insert(ObjectAttribute::Deadly);
    }

    // Override update: do nothing
    UpdateResult update(GameState& gameState) {
        return UpdateResult::None;
    }

    // Override rendering
    RenderData getRenderData() {
        frameCount++;
        return {
            RenderType::Image,
            coordType,
            locx,
            locy - sin(frameCount / 80.0) * 0.3,
            width,
            height + sin(frameCount / 80.0) * 0.3,
            { 255, 0, 0 },
            "assets/spike.png"
        };
    }
};
