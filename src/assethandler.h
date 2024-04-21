#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

// Handle access of all assets to reduce repeated work
class AssetHandler {
private:
    std::map<std::string, sf::Image> images;
    bool mainFontLoaded = false;
    sf::Font mainFont;

public:
    // Get the image from a path (ex. "assets/tiv_logo.png")
    sf::Image getImage(std::string path);
    // Get the main font
    sf::Font& getMainFont();
};
