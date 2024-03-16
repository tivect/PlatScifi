#pragma once

#include "renderdata.h"

// Stores a world object
class WorldObject {
protected:
    CoordType coordType;
    double locx;
    double locy;
    double width;
    double height;

public:
    // Create the WorldObject
    WorldObject() {
        coordType = CoordType::World;
        locx = 0.0;
        locy = 0.0;
        width = 1.0;
        height = 1.0;
    }

    // Update each frame
    void update(/*WorldState& worldState*/);

    // Return the results to render
    RenderData getRenderData();
};
