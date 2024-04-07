#include "renderer.h"

Renderer::Renderer(sf::RenderWindow& window, AssetHandler& assetHandler)
    : window(window), assetHandler(assetHandler) {
        // Update the camera defaults if needed
        if (LEVEL_DESIGN_MODE) {
            screenPixPerWorld = 10; // Zoom out
        }
    }

void Renderer::renderFromData(RenderData data) {
    // TODO: implement other types (like images)
    if (data.type == RenderType::Rectangle) {
        // Rectangle
        sf::RectangleShape toRender;
        if (data.coordType == CoordType::Screen) {
            // Literal coordinates
            toRender.setSize(sf::Vector2f(data.width, data.height));
            toRender.setPosition(sf::Vector2f(data.locx, data.locy));
        } else {
            // Convert from world to screen coordinates
            // TODO: render from the center position?
            // TODO: do not render if out of screen range
            toRender.setSize(sf::Vector2f(data.width * screenPixPerWorld, data.height * screenPixPerWorld));
            toRender.setPosition(sf::Vector2f((data.locx - worldCameraCenterX) * screenPixPerWorld + window.getSize().x / 2.0, (data.locy - worldCameraCenterY) * screenPixPerWorld + window.getSize().y / 2.0));
        }
        toRender.setFillColor(sf::Color(data.color.r, data.color.g, data.color.b));
        window.draw(toRender);
    } else if (data.type == RenderType::Circle) {
        // Circle
        sf::CircleShape toRender;
        if (data.coordType == CoordType::Screen) {
            // Literal coordinates
            toRender.setRadius((data.width + data.height) / 4);
            toRender.setPosition(sf::Vector2f(data.locx, data.locy));
        } else {
            // Convert from world to screen coordinates
            // TODO: render from the center position?
            toRender.setRadius((data.width + data.height) / 4 * screenPixPerWorld);
            toRender.setPosition(sf::Vector2f((data.locx - worldCameraCenterX) * screenPixPerWorld + window.getSize().x / 2.0, (data.locy - worldCameraCenterY) * screenPixPerWorld + window.getSize().y / 2.0));
        }
        toRender.setFillColor(sf::Color(data.color.r, data.color.g, data.color.b));
        window.draw(toRender);
    } else {
        // Image
        // Load the image source file
        // TODO: refactor loading the texture as well?
        sf::Image img = assetHandler.getImage(data.imageSource);
        sf::Texture tex;
        sf::Sprite toRender;
        if (data.coordType == CoordType::Screen) {
            // Literal coordinates
            tex.create(img.getSize().x, img.getSize().y);
            tex.update(img);
            toRender.setTexture(tex);
            toRender.setPosition(data.locx, data.locy);
            toRender.setScale(data.width / img.getSize().x, data.height / img.getSize().y);
        } else {
            // Convert from world to screen coordinates
            // TODO: render from the center position?
            tex.create(img.getSize().x, img.getSize().y);
            tex.update(img);
            toRender.setTexture(tex);
            toRender.setPosition(sf::Vector2f((data.locx - worldCameraCenterX) * screenPixPerWorld + window.getSize().x / 2.0, (data.locy - worldCameraCenterY) * screenPixPerWorld + window.getSize().y / 2.0));
            toRender.setScale(data.width * screenPixPerWorld / img.getSize().x, data.height * screenPixPerWorld / img.getSize().y);
        }
        window.draw(toRender);
    }
}

void Renderer::renderMessage(UIMessage& uiMessage, int locx, int locy) {
    sf::Text text;
    text.setFont(assetHandler.getMainFont());
    text.setString(uiMessage.message);
    text.setCharacterSize(uiMessage.fontSize);
    text.setFillColor(sf::Color(uiMessage.color.r, uiMessage.color.g, uiMessage.color.b));
    text.setPosition(locx, locy);
    window.draw(text);
}

void Renderer::setCamera(double newWorldCameraCenterX, double newWorldCameraCenterY, double percentEasing) {
    worldCameraCenterX = worldCameraCenterX * percentEasing + newWorldCameraCenterX * (1 - percentEasing);
    worldCameraCenterY = worldCameraCenterY * percentEasing + newWorldCameraCenterY * (1 - percentEasing);
}

void Renderer::renderWorld(GameState& gameState) {
	// Clear/render sky
	window.clear(sf::Color(111, 201, 252));
	// Render world objects
    for (WorldObject* object : gameState.objects) {
        renderFromData(object->getRenderData());
    }

	// TODO: render on-screen debug messages (ex. "enemy_fipa spawned")
    // Render UI messages
    int level = 0;
    for (int i = gameState.uiMessages.size() - 1; i >= 0; i--) {
        renderMessage(gameState.uiMessages[i], 24, 24 + level * 20);
        level++;
    }
    // Render other UI
    UIMessage levelName = { gameState.getLevelName(), { 255, 255, 255 }, 24 };
    renderMessage(levelName, window.getSize().x - 140, 18);
}
