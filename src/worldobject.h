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
    WorldObject();

    // Update each frame
    virtual void update(/*WorldState& worldState*/);

    // Return the results to render
    virtual RenderData getRenderData();
};
