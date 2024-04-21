#pragma once

#include "../worldobject.h"
#include "../constants.h"

// The data for the player
class Player : public WorldObject {
private:
    bool onGround = false;
    int deathCounter = 0;

public:
    // Constructor
    Player(double spawnx, double spawny) : WorldObject() {
        locx = spawnx;
        locy = spawny;
        objectAttributes.insert(ObjectAttribute::Persist);
    }

    // Input: acceleration
    void accelerate(double deltax, double deltay) {
        velx += deltax;
        vely += deltay;
    }

    // Input: jump
    void jump() {
        if (onGround) {
            vely = -0.5;
        }
    }

    double getLocx() {
        return locx;
    }

    double getLocy() {
        return locy;
    }

    int getDeathCounter() {
        return deathCounter;
    }

    void die() {
        deathCounter++;
        // Reset position and physics
        teleport(5, 10);
        velx = 0;
        vely = 0;
        onGround = false;
    }

    void teleport(double locx, double locy) {
        this->locx = locx;
        this->locy = locy;
    }

    // Override update: gravity and acceleration
    UpdateResult update(GameState& gameState);

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
            { 0, 255, 0 },
            ""
        };
    }
};
