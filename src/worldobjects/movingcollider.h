#pragma once

#include "../worldobject.h"

// An object that does not move, but that other objects can collide with
class MovingCollider : public WorldObject {
private:
    long periodFrames;
    long frameCount = 0;
    double spawnx;
    double spawny;
    double targetx;
    double targety;

public:
    // Constructor
    MovingCollider(
        double spawnx, double spawny, double width, double height,
        long periodFrames, double targetx, double targety
    ) : WorldObject() {
        locx = spawnx;
        locy = spawny;
        this->spawnx = spawnx;
        this->spawny = spawny;
        this->width = width;
        this->height = height;
        this->periodFrames = periodFrames;
        this->targetx = targetx;
        this->targety = targety;
        objectAttributes.insert(ObjectAttribute::Collision);
    }

    // Override update: interpolation
    UpdateResult update(GameState& gameState) {
        double alpha = sin(2 * 3.14159 * frameCount / periodFrames) * 0.5 + 0.5;
        // Interpolate between positions
        double locxnew = spawnx * (1.0 - alpha) + targetx * (alpha);
        double locynew = spawny * (1.0 - alpha) + targety * (alpha);
        this->velx = locxnew - this->locx;
        this->vely = locynew - this->locy;
        this->locx = locxnew;
        this->locy = locynew;
        frameCount++;
        return UpdateResult::None;
    }

    // Override rendering
    RenderData getRenderData() {
        return {
            RenderType::Image,
            coordType,
            locx,
            locy,
            width,
            height,
            { 14, 92, 81 },
            "assets/yellowpad.png"
        };
    }
};
