#pragma once

#include <string>

class WorldState {
private:
    std::string levelName;
    float gravityStrength = 0.01;

public:
    // Get the current level name
    std::string getLevelName();
    // Get the current gravity field strength
    float getGravityStrength();
};
