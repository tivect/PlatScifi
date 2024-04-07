#pragma once

#include <vector>
#include <set>
#include "renderdata.h"
#include "worldstate.h"

// The result of an update function
enum class UpdateResult {
    None,
    Destroy,
    DieReset,
    NextLevel // TODO: better naming
};

// The attributes that an object can have
enum class ObjectAttribute {
    OverlapDetect,
    Collision,
    Deadly,
    LevelTeleport,
    Persist // Persist across levels
};

// Stores a world object
class WorldObject {
protected:
    CoordType coordType;
    double locx;
    double locy;
    double width;
    double height;
    std::set<ObjectAttribute> objectAttributes;

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

    bool hasAttribute(ObjectAttribute attribute);

    // TODO: get whether a rectangle is inside of this object

    // Return the results to render
    virtual RenderData getRenderData();
};
