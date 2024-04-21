#pragma once

#include <string>
#include "renderdata.h"

// A message with a designated text color
struct UIMessage {
    std::string message;
    Color color;
    int fontSize = 14;
    long durationFramesRemaining = 150;
    // Update the UI message, returning whether it should be deleted
    bool update() {
        durationFramesRemaining--;
        return durationFramesRemaining <= 0;
    }
};
