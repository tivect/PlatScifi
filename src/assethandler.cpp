#include "assethandler.h"
#include <iostream> // DEBUGGING
					// ONLY

sf::Image AssetHandler::getImage(std::string path) {
    // Return if image already exists
    if (images.find(path) != images.end()) {
        return images[path];
    }
    // Create a new image, add it to the cache, and return
    sf::Image img;
    if (!img.loadFromFile(path)) {
        // Error
        // TODO: handle
    }
    images[path] = img;
    return img;
}

// Get a reference to the font, not a copy
sf::Font& AssetHandler::getMainFont() {
	if (mainFontLoaded) return mainFont;
    if (!mainFont.loadFromFile("assets/LiberationSans-Regular.ttf")) {
        // Error
		std::cout << "ERR: Failed to load 'assets/LiberationSans-Regular.ttf'" << std::endl;
		// TODO: handle
    }
    mainFontLoaded = true;
    return mainFont;
}
