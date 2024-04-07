#include "animal.h"

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
                ObjectAttribute::OverlapDetect,
                ObjectAttribute::Deadly
            }
        }
    }
};
