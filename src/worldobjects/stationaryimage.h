#pragma once

#include "../worldobject.h"

// Stores a stationary image at a point in space
class StationaryImage : public WorldObject {
private:
    std::string filename;

public:
    // Constructor: provide the name of the asset from assets (ex. "assets/tiv_logo.png")
    StationaryImage(double spawnx, double spawny, double width, double height, std::string filename) : WorldObject() {
        locx = spawnx;
        locy = spawny;
        this->width = width;
        this->height = height;
        this->filename = filename;
    }

    // Override update: do nothing
    UpdateResult update() {
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
            { 255, 0, 0 },
            filename
        };
    }
};
