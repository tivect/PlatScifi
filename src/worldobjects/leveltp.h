#pragma once

#include "../worldobject.h"

// An object that teleports the player to another level
class LevelTp : public WorldObject {
private:
    long frameCount = 0;

public:
    // Constructor
    LevelTp(double spawnx, double spawny) : WorldObject() {
        locx = spawnx;
        locy = spawny;
        this->width = 1;
        this->height = 1;
        this->objectAttributes.insert(ObjectAttribute::OverlapDetect);
	    this->objectAttributes.insert(ObjectAttribute::LevelTeleport);
    }

    // Override update: check with player ?
    UpdateResult update(GameState& gameState) {
        // TODO: stuff
        return UpdateResult::None;
    }

    // Override rendering
    RenderData getRenderData() {
        frameCount++;
        // TODO: image?
        return {
            RenderType::Rectangle,
            coordType,
            locx + sin(frameCount / 20.0) * 0.3,
            locy + cos(frameCount / 20.0) * 0.3,
            width,
            height,
            { 66, 135, 245 },
            ""
        };
    }
};
