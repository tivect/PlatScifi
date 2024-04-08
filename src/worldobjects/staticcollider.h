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
        objectAttributes.insert(ObjectAttribute::Collision);
    }

    // Override update: gravity
    UpdateResult update(GameState& gameState) {
        return UpdateResult::None;
    }

    // Override rendering
    RenderData getRenderData() {
        // TODO: image/animations
        return {
            RenderType::Image,
            coordType,
            locx,
            locy,
            width,
            height,
            { 14, 92, 81 },
            "assets/grass1.png" // TODO: allow rendering sand
        };
    }
};
