#pragma once

#include "../worldobject.h"
#include "../constants.h"

// The data for an animal in the world
class Animal : public WorldObject {
private:
    double velx = 0;
    double vely = 0;
    bool onGround = false;
    long frameCount = 0;
	int animFrameNum = 0;
	int animFrameMax = 1;

public:
    // Constructor
    Animal(double spawnx, double spawny) : WorldObject() {
        locx = spawnx;
        locy = spawny;
		width = 2.0;
		height = 2.0;
		objectAttributes.insert(ObjectAttribute::Collision);
    }

	// TODO: different AI based on animal type (enum? stringly typed?)

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

    void teleport(double locx, double locy) {
        this->locx = locx;
        this->locy = locy;
    }

    // Override update: gravity and acceleration, and AI logic
    UpdateResult update(WorldState& worldState, std::vector<WorldObject*>& objects) {
		// AI Logic
		accelerate(-0.01, 0);
		jump();
		// Physics
        if (!LEVEL_DESIGN_MODE) {
            vely += worldState.getGravityStrength();
        }
        velx *= 0.88;
        vely *= 0.96;
        locx += velx;
        locy += vely;
        // Check collision and update
        onGround = false;
        // TODO: refactor
        // TODO: update all collisions from player
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
            }
            if (object->hasAttribute(ObjectAttribute::OverlapDetect)) {
                // Check overlap only
                if (locy + height >= object->getLocy() && locy < object->getLocy() + object->getHeight()) {
                    if (locx + width > object->getLocx() && locx < object->getLocx() + object->getWidth()) {
                        // Hit
                        overlapped = true;
                    }
                }
            }
        }
		// TODO: out of bounds respawn/death
        return UpdateResult::None;
    }

    // Override rendering
    RenderData getRenderData() {
		frameCount++;
		if (frameCount % 10 == 0) {
			animFrameNum++;
			if (animFrameNum > animFrameMax) animFrameNum = 0;
		}
        return {
            RenderType::Image,
            coordType,
            locx,
            locy,
            width,
            height,
            { 255, 0, 0 },
            "assets/enemy_bird_" + std::to_string(animFrameNum) + ".png"
        };
    }
};
