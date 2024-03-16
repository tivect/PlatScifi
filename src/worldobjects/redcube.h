#pragma once

#include "worldobject.h"

// Stores a red cube
class RedCube : WorldObject {
public:
    // Override update: move right over time
    void update() {
        locx += 0.1;
    }

    // TODO: MAKE SURE IT OVERRIDES
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
