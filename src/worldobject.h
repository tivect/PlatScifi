#pragma once

#include <vector>
#include "renderdata.h"
#include "worldstate.h"

// The result of an update function
enum class UpdateResult {
    None,
    Destroy
};

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
    virtual UpdateResult update(WorldState& worldState, std::vector<WorldObject*>& objects);

    // Get whether a point is inside of this object
    double isPointInside(double x, double y);

    double getLocx();
    double getLocy();
    double getWidth();
    double getHeight();

    // TODO: get whether a rectangle is inside of this object

    // Return the results to render
    virtual RenderData getRenderData();
};
