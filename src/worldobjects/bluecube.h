#pragma once

#include "worldobject.h"

// Store a blue cube
class BlueCube : public WorldObject {
private:
    double velx = 0.3;
    double vely = 0.15;

public:
    BlueCube() : WorldObject() {}
    
    // Override the update function
    UpdateResult update() {
        locx += velx;
        if (locx > 64 || locx < 0) velx *= -1;
        locy += vely;
        if (locy > 36 || locy < 0) vely *= -1;
        
        return UpdateResult::None;
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
