#pragma once

#include <vector>
#include <set>
#include "renderdata.h"
#include "worldstate.h"

// To fix the cyclical dependency error
class GameState;

// The result of an update function
enum class UpdateResult {
    None,
    Destroy,
    DieReset,
    NextLevel, // TODO: better naming
    ReplicateAndDestroy,
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
    double velx;
    double vely;
    std::set<ObjectAttribute> objectAttributes;

public:
    // Create the WorldObject
    WorldObject();

    // Update each frame
    virtual UpdateResult update(GameState& gameState);

    // Get whether a point is inside of this object
    double isPointInside(double x, double y);

    double getLocx();
    double getLocy();
    double getWidth();
    double getHeight();
    double getVelx();
    double getVely();

    void debugCyclical(GameState& gameState);

    bool hasAttribute(ObjectAttribute attribute);

    // TODO: get whether a rectangle is inside of this object

    // Return the results to render
    virtual RenderData getRenderData();
};
