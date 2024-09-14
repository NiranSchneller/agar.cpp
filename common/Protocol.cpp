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


