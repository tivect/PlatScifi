#pragma once

#include "../worldobject.h"

// Stores a red cube for debugging purposes
class RedCube : public WorldObject {
public:
    // Constructor
    RedCube(double spawnx, double spawny) : WorldObject() {
        locx = spawnx;
        locy = spawny;
    }

    // Override update: move right over time
    UpdateResult update() {
        locx += 0.1;
        if (locx > 30) {
            locy += 1;
            locx = 0;
        }
        return UpdateResult::None;
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
