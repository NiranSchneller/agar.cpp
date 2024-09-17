#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "Blob.h"
class Graphics {
private:
	sf::RenderWindow gameWindow;
public:
	Graphics(int screenWidth, int screenHeight);
	void drawAllBlobs(std::vector<std::unique_ptr<Blob>>& blobsToDraw);
	sf::RenderWindow& getGameWindow();
	void drawBlob(Blob& blob);
};

#endif // !GRAPHICS_H
