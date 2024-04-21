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
    UpdateResult update(GameState& gameState);

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
