#pragma once

#include "worldobject.h"

// Stores a red cube for debugging purposes
class RedCube : public WorldObject {
public:
    // Constructor
    RedCube(double spawnx, double spawny) : WorldObject() {
        locx = spawnx;
        locy = spawny;
    }

    // TODO: ENSURE OVERRIDING WORKS
    // Override update: move right over time
    void update() {
        locx += 0.1;
        if (locx > 30) {
            locy += 1;
            locx = 0;
        }
    }

    // Override rendering
    RenderData getRenderData() {
        return {
            RenderType::Rectangle,
            coordType,
            locx,
            locy,
            width,
            height,
            { 255, 0, 0 },
            ""
        };
    }
};
