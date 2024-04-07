#pragma once

#include "../worldobject.h"
#include "../constants.h"

// The data for the player
class Player : public WorldObject {
private:
    double velx = 0;
    double vely = 0;
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
    UpdateResult update(WorldState& worldState, std::vector<WorldObject*>& objects) {
        if (!LEVEL_DESIGN_MODE) {
            vely += worldState.getGravityStrength();
        }
        velx *= 0.88;
        vely *= 0.96;
        locx += velx;
        locy += vely;
        // Check collision and update
        UpdateResult updateResultToReturn = UpdateResult::None;
        onGround = false;
        // TODO: refactor
        // TODO: only check with types enabling collision
        // TODO: polygonal collisions
        // TODO: when hitting multiple?
        // TODO: impart velocity on collisions (ex. moving platforms)
        for (WorldObject* object : objects) {
            if (object == this) continue;
            bool collided = false;
	        bool overlapped = false;
            if (object->hasAttribute(ObjectAttribute::Collision)) {
                // X movement pushout
                // todo: better way of doing the 0.1 thing (subtract velocity instead?)
                if (locy + height - 0.1 >= object->getLocy() && locy + 0.1 < object->getLocy() + object->getHeight()) {
                    // Within the y
                    if (locx + width > object->getLocx() && locx < object->getLocx() + object->getWidth()) {
                        // Side wall
                        locx -= velx;
                        velx = 0;
                        collided = true;
			            overlapped = true;
                    }
                }
                if (locx + width >= object->getLocx() && locx < object->getLocx() + object->getWidth()) {
                    // Within the x
                    if (locy + height > object->getLocy() && locy < object->getLocy() + object->getHeight()) {
						if (locy > object->getLocy() + object->getHeight() / 2.0) {
							// Ceiling
							if (vely >= 0) {
								// Already traveling down: do nothing
							} else {
								// Traveling up: stop
								locy -= vely;
								vely = 0;
							}
							collided = true;
							overlapped = true;
						} else {
							// Floor
							locy -= vely;
							vely = 0;
							collided = true;
							overlapped = true;
							// todo: should not be on ground on a bottom corner
							onGround = true;
						}
                    }
                }
            } else if (object->hasAttribute(ObjectAttribute::OverlapDetect)) {
                // Check overlap only
                if (locy + height >= object->getLocy() && locy < object->getLocy() + object->getHeight()) {
                    if (locx + width > object->getLocx() && locx < object->getLocx() + object->getWidth()) {
                        // Hit
                        overlapped = true;
                    }
                }
            }
            // Collision stuff
            if (overlapped && object->hasAttribute(ObjectAttribute::Deadly)) {
                // Die
                die();
                updateResultToReturn = UpdateResult::DieReset; 
            }
            if (overlapped && object->hasAttribute(ObjectAttribute::LevelTeleport)) {
                // Teleport to the next level
                // TODO: impl better
                teleport(5, 10);
                return UpdateResult::NextLevel;
            }
        }
		// TODO: out of bounds respawn/death (and restart level/message on die)
        return updateResultToReturn;
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
            { 0, 255, 0 },
            ""
        };
    }
};
