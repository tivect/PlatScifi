#pragma once

#include "../worldobject.h"

// The data for the player
class Player : public WorldObject {
private:
    float velx = 0;
    float vely = 0;

public:
    // Constructor
    Player(double spawnx, double spawny) : WorldObject() {
        locx = spawnx;
        locy = spawny;
    }

    // Input: acceleration
    // TODO: accelerate instead of move
    void accelerate(double deltax, double deltay) {
        velx += deltax;
        vely += deltay;
    }

    // Input: jump
    void jump() {
        vely = -0.4;
    }

    double getLocx() {
        return locx;
    }

    double getLocy() {
        return locy;
    }

    // Override update: gravity and acceleration
    UpdateResult update(WorldState& worldState, std::vector<WorldObject*>& objects) {
        vely += worldState.getGravityStrength();
        velx *= 0.96;
        vely *= 0.96;
        locx += velx;
        locy += vely;
        //if (velx < 0.01 && velx >= -0.01) velx = 0;
        // Check collision
        // todo: refactor
        // todo: only check with types enabling collision
        // todo: when hitting multiple?
        for (WorldObject* object : objects) {
            if (object == this) continue;
            // X movement pushout
            // todo: better way of doing the 0.1 thing
            if (locy + height - 0.1 >= object->getLocy() && locy + 0.1 < object->getLocy() + object->getHeight()) {
                // Within the y
                if (locx + width > object->getLocx() && locx < object->getLocx() + object->getWidth()) {
                    // Side wall
                    locx -= velx;
                    velx = 0;
                }
            }
            if (locx + width >= object->getLocx() && locx < object->getLocx() + object->getWidth()) {
                // Within the x
                if (locy + height > object->getLocy() && locy < object->getLocy() + object->getHeight()) {
                    // Floor/ceiling
                    locy -= vely;
                    vely = 0;
                }
            }
        }
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
