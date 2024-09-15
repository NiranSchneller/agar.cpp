#include <SFML/Graphics.hpp>
#include "Graphics.h"
#include <memory>

Graphics::Graphics(int screenWidth, int screenHeight) {
	this->gameWindow.create(sf::VideoMode(screenWidth, screenHeight), "Agar.cpp!");

}

/*
	Assumes each blob in blobsToDraw has relevant coordinates (all respect screen resolution etc).
*/
void Graphics::drawAllBlobs(std::vector<std::unique_ptr<Blob>> blobsToDraw) {
	for (size_t i = 0; i < blobsToDraw.size(); i++) {
		drawBlob(std::move(blobsToDraw.at(i)));
	}
}

void Graphics::drawBlob(std::unique_ptr<Blob> blob) {
	sf::CircleShape circleToDraw = blob->blobToCircle();
	this->gameWindow.draw(circleToDraw);
}

sf::RenderWindow& Graphics::getGameWindow() {
	return this->gameWindow;
}
