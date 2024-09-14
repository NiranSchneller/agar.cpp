#include <SFML/Graphics.hpp>
#include "Graphics.h"


Graphics::Graphics(int screenWidth, int screenHeight) {
	this->gameWindow.create(sf::VideoMode(screenWidth, screenHeight), "Agar.cpp!");

}

/*
	Assumes each blob in blobsToDraw has relevant coordinates (all respect screen resolution etc).
*/
void Graphics::drawAllBlobs(std::vector<Blob*> blobsToDraw) {
	for (size_t i = 0; i < blobsToDraw.size(); i++) {
		drawBlob(*blobsToDraw.at(i));
	}
}

void Graphics::drawBlob(Blob& blob) {
	sf::CircleShape circleToDraw = blob.blobToCircle();
	this->gameWindow.draw(circleToDraw);
}

sf::RenderWindow& Graphics::getGameWindow() {
	return this->gameWindow;
}
