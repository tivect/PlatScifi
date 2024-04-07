#pragma once

#include <map>
#include <vector>
#include "../worldobject.h"
#include "../constants.h"

// The default data for a specific animal type
struct AnimalData {
    std::string displayName;
    std::string texturePrefix;
    double textureScale;
    int animFrameMax;
    double width;
    double height;
    std::set<ObjectAttribute> objectAttributes;
};

// The data for an animal in the world
class Animal : public WorldObject {
private:
    bool onGround = false;
    long frameCount = 0;
    std::string texturePrefix;
    double textureScale = 1.0;
	int animFrameNum = 0;
	int animFrameMax = 1;
    bool moveRight = false;
    std::string name = "unnamed";

public:
    // Define the default data for all named animals (<name, data>)
    static const std::map<std::string, AnimalData> animalDefaults;

    // Constructor (define everything specifically)
    Animal(std::string texturePrefix, int animFrameMax, double spawnx, double spawny) : WorldObject() {
        locx = spawnx;
        locy = spawny;
		width = 2.0;
		height = 2.0;
        this->texturePrefix = texturePrefix;
        this->animFrameMax = animFrameMax;
		objectAttributes.insert(ObjectAttribute::Collision);
    }

    // Constructor for named animals
    Animal(std::string name, double spawnx, double spawny) : WorldObject() {
        locx = spawnx;
        locy = spawny;
        if (animalDefaults.find(name) == animalDefaults.end()) {
            // Could not find the animal
            name = "bird";
        }
        this->name = name;
        width = (*animalDefaults.find(name)).second.width;
        height = (*animalDefaults.find(name)).second.height;
        this->texturePrefix = (*animalDefaults.find(name)).second.texturePrefix;
        this->textureScale = (*animalDefaults.find(name)).second.textureScale;
        this->animFrameMax = (*animalDefaults.find(name)).second.animFrameMax;
        objectAttributes = (*animalDefaults.find(name)).second.objectAttributes;
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

    void reverseDirection() {
        moveRight = !moveRight;
    }

    void setDimensions(double newWidth, double newHeight) {
        this->width = newWidth;
        this->height = newHeight;
    }

    // Override update: gravity and acceleration, and AI logic
    UpdateResult update(WorldState& worldState, std::vector<WorldObject*>& objects) {
		// AI Logic
        UpdateResult updateResultToReturn = UpdateResult::None;
		accelerate(moveRight ? 0.01 : -0.01, 0);
		jump();
        // Special named animal abilities
        // TODO: change from stringly typed?
        if (name == "replicator") {
            // Replicate after 300 frames
            if (frameCount >= 300) {
                // Replicate
                updateResultToReturn = UpdateResult::ReplicateAndDestroy;
            } else if (frameCount >= 293) {
                animFrameNum = 2;
            } else if (frameCount >= 285) {
                animFrameNum = 1;
            }
        }

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
                        // For AI
                        moveRight = !moveRight;
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
        }
		// TODO: out of bounds respawn/death
        return updateResultToReturn;
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
            locx - width * ((textureScale - 1.0) / 2.0),
            locy - height * ((textureScale - 1.0) / 2.0),
            width * textureScale,
            height * textureScale,
            { 255, 0, 0 },
            "assets/" + texturePrefix + "_" + std::to_string(animFrameNum) + ".png"
        };
    }
};
