#pragma once

#include "../worldobject.h"

// An object that does not move, but that other objects can collide with
// (deadly to player)
class StaticDeadly : public WorldObject {
public:
    // Constructor
    StaticDeadly(double spawnx, double spawny, double width, double height) : WorldObject() {
        locx = spawnx;
        locy = spawny;
        this->width = width;
        this->height = height;
        objectAttributes.insert(ObjectAttribute::Collision);
	objectAttributes.insert(ObjectAttribute::Deadly);
    }

    // Override update
    UpdateResult update(GameState& gameState) {
        return UpdateResult::None;
    }

    // Override rendering
    RenderData getRenderData() {
        // TODO: image?
        return {
            RenderType::Rectangle,
            coordType,
            locx,
            locy,
            width,
            height,
            { 207, 12, 19 },
            ""
        };
    }
};
