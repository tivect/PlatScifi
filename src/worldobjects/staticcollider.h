#pragma once

#include "../worldobject.h"

// An object that does not move, but that other objects can collide with
class StaticCollider : public WorldObject {
public:
    // Constructor
    StaticCollider(double spawnx, double spawny, double width, double height) : WorldObject() {
        locx = spawnx;
        locy = spawny;
        this->width = width;
        this->height = height;
    }

    // Override update: gravity
    UpdateResult update(WorldState& worldState, std::vector<WorldObject*>& objects) {
        return UpdateResult::None;
    }

    // Override rendering
    RenderData getRenderData() {
        // TODO: image/animations
        return {
            RenderType::Rectangle,
            coordType,
            locx,
            locy,
            width,
            height,
            { 14, 92, 81 },
            ""
        };
    }
};
