#pragma once

#include "../worldobject.h"

// The data for the player
class Player : public WorldObject {
public:
    // Constructor
    Player(double spawnx, double spawny) : WorldObject() {
        locx = spawnx;
        locy = spawny;
    }

    // Input: movement
    // TODO: accelerate instead of move
    void move(double deltax, double deltay) {
        locx += deltax;
        locy += deltay;
    }

    double getLocx() {
        return locx;
    }

    double getLocy() {
        return locy;
    }

    // Override update: do nothing (yet)
    UpdateResult update() {
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
            { 255, 0, 0 },
            ""
        };
    }
};
