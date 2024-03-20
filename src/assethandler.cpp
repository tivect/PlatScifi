#include "assethandler.h"

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
