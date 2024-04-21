#include "animal.h"
#include "../gamestate.h"

// Define the default data for all named animals (<name, data>)
const std::map<std::string, AnimalData> Animal::animalDefaults = {
    {
        "bird", // Name
        {
            "Bird", // Display name
            "enemy_bird", // Texture prefix
            1.0, // Texture scale
            1, // Animation frame max
            2.0, // Width
            2.0, // Height
            {
                // Object attributes
                ObjectAttribute::Collision
            }
        }
    },
    {
        "fipa",
        {
            "Fipa",
            "enemy_fipa",
            1.2,
            0,
            3.0,
            3.0,
            {
                ObjectAttribute::Collision,
                ObjectAttribute::Deadly
            }
        }
    },
    {
        "replicator",
        {
            "Replicator",
            "enemy_replicator",
            2.0,
            0,
            3.0,
            3.0,
            {
                ObjectAttribute::Collision,
                ObjectAttribute::Deadly
            }
        }
    },
    {
        "addax",
        {
            "Addax",
            "enemy_addax",
            2.0,
            0,
            3.0,
            3.0,
            {
                ObjectAttribute::Collision
            }
        }
    }
};

UpdateResult Animal::update(GameState& gameState) {
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
        vely += gameState.getWorldState().getGravityStrength();
    }
    velx *= 0.88;
    vely *= 0.96;
    locx += velx;
    locy += vely;
    // Check collision and update
    onGround = false;
    // TODO: refactor
    // TODO: update all collisions from player
    std::set<WorldObject*> nearby = gameState.getCollisionMatrix().searchMatrix(this);
    for (WorldObject* object : nearby) {
        if (object == this) continue;
        bool collided = false;
        bool overlapped = false;
        if (object->hasAttribute(ObjectAttribute::Collision)) {
            // X movement pushout
            // todo: improve time complexity (O(n^2) :skull:)
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
