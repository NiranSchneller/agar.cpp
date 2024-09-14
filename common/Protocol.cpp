#include <SFML/Graphics.hpp>
#include "Protocol.h"
#include "Constants.h"
#include "Utilities.h"

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

std::string Protocol::sendClientInformationToServer(Point mousePosition) { return ""; }
Point Protocol::getClientInformationFromClient(std::string message) { return NULL; }

/*
	From server to client.
*/
// A list of blobs that the client will draw on screen.
std::string Protocol::sendBlobToDrawToClient(std::vector<Blob>& blobsToDraw) { return NULL; }
// Reverse of sendBlobToDrawToClient, will convert from string back to list.
std::vector<Blob*> Protocol::getBlobsToDrawFromServer(std::string message) { std::vector<Blob*> blob; return blob; }

