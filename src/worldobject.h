#pragma once

#include <vector>
#include "renderdata.h"
//#include "worldstate.h"

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
    virtual UpdateResult update(/*WorldState& worldState*/);

    // TODO: delete this function
    void tester(std::vector<WorldObject*>& v) {
        // Do stuff with v
    }

    // Return the results to render
    virtual RenderData getRenderData();
};
