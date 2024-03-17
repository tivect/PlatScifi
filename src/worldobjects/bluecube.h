#pragma once

#include "worldobject.h"

// Store a blue cube
class BlueCube : public WorldObject {
public:
    BlueCube() : WorldObject() {}
    
    // Override the update function
    void update() {
        locx += 0.3;
        locy += 0.15;
    }

    // Override the render function
    RenderData getRenderData() {
        return {
            RenderType::Circle,
            coordType,
            locx,
            locy,
            width,
            height,
            { 0, 30, 255 },
            ""
        };
    }
};
