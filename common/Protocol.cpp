#include <SFML/Graphics.hpp>
#include "Protocol.h"
#include "Constants.h"
#include "Utilities.h"
#include <memory>
#include <iostream>

std::string Protocol::sendInitialInformationToServer(int resWidth, int resHeight, int titleBarSize) {
	return std::to_string(resWidth) + DELIMETER + std::to_string(resHeight) 
					  + DELIMETER + std::to_string(titleBarSize);
}

std::vector<int> Protocol::getInitialInformationFromClient(std::string message) {
	std::vector<int> out;
	std::vector<std::string> splitMessage = Utilities::splitByDelimeter(message, DELIMETER);
	for (unsigned short i = 0; i < splitMessage.size(); i++) {
		out.push_back(stoi(splitMessage.at(i)));
	}
	return out;
}

std::string Protocol::sendClientInformationToServer(Point mousePosition) {
	std::string out;
	out = std::to_string(mousePosition.GetX()) + DELIMETER + std::to_string(mousePosition.GetY());
	return out;
}

Point Protocol::getClientInformationFromClient(std::string message) {
	std::vector<std::string> splitMessage = Utilities::splitByDelimeter(message, DELIMETER);
	Point out(stoi(splitMessage.at(0)), stoi(splitMessage.at(1)));
	return out;
}

/*
	From server to client.
*/
// A list of blobs that the client will draw on screen.
std::string Protocol::sendBlobToDrawToClient(std::vector<std::unique_ptr<Blob>> blobsToDraw) {
	std::string out;

	std::unique_ptr<Blob> currentBlob;
	sf::Color color;
	Point blobPos;
	std::string blobName;
	double radius;
	std::string colorInText;
	std::string posInText;

	if (blobsToDraw.size() == 0) {
		return "";
	}

	for (int i = 0; i < blobsToDraw.size() - 1; i++) { // We don't want to add delimeter in the last time
		currentBlob = std::make_unique<Blob>(
			blobsToDraw.at(i)->getBlobName(),
			blobsToDraw.at(i)->getRadius(),
			blobsToDraw.at(i)->getPosition(),
			blobsToDraw.at(i)->getColor()
		);
		blobName = currentBlob->getBlobName();
		radius = currentBlob->getRadius();
		color = currentBlob->getColor();
		blobPos = currentBlob->getPosition();

		colorInText = std::to_string(color.r) + ',' + std::to_string(color.g)
							+ ',' + std::to_string(color.b) + ',' + std::to_string(color.a);
		posInText = std::to_string(blobPos.GetX()) + ',' + std::to_string(blobPos.GetY());

		out += blobName + ',' + std::to_string(radius) + ',' + posInText + ',' + colorInText + DELIMETER;
	}

	currentBlob = std::move(blobsToDraw.at(blobsToDraw.size() - 1));
	blobName = currentBlob->getBlobName();
	radius = currentBlob->getRadius();
	color = currentBlob->getColor();
	blobPos = currentBlob->getPosition();

	colorInText = std::to_string(color.r) + ',' + std::to_string(color.g)
		+ ',' + std::to_string(color.b) + ',' + std::to_string(color.a);
	posInText = std::to_string(blobPos.GetX()) + ',' + std::to_string(blobPos.GetY());

	out += blobName + ',' + std::to_string(radius) + ',' + posInText + ',' + colorInText;

	return out;
}


// Reverse of sendBlobToDrawToClient, will convert from string back to list.
std::vector<std::unique_ptr<Blob>> Protocol::getBlobsToDrawFromServer(std::string message) {

	std::vector<std::unique_ptr<Blob>> blobsToDraw;
	std::vector<std::string> splitMessage = Utilities::splitByDelimeter(message, DELIMETER);
	std::vector<std::string> splitBlob;
	Blob blob(0, Point::Point(0,0));
	sf::Color blobColor;
	for (size_t i = 0; i < splitMessage.size(); i++) {
		
		splitBlob = Utilities::splitByDelimeter(splitMessage.at(i), ",");
		// Reverse of sendBlobToDrawToClient (for loop section)
		blob.setBlobName(splitBlob.at(0));
		blob.setRadius(stod(splitBlob.at(1)));
		blob.setPosition(Point::Point(stod(splitBlob.at(2)), stod(splitBlob.at(3))));
		
		blob.setColor(sf::Color::Color(stoi(splitBlob.at(4)), stoi(splitBlob.at(5)),
						stoi(splitBlob.at(6)), stoi(splitBlob.at(7))));

		blobsToDraw.push_back(std::make_unique<Blob>(blob.getBlobName(), blob.getRadius(), blob.getPosition(), blob.getColor()));
	}
	return blobsToDraw;
}

