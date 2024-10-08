#ifndef UTILITIES_H
#define UTILITIES_H
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <WinSock2.h>
#include "Point.h"
class Utilities
{
public:
	/*
	The size of the message is NOT including size header + first delimeter.

	If message "SOCKET ERROR XXX" is returned, then an error has occurred.

	*/
	static std::string recieveSocketMessage(SOCKET socket);
	
	/*
	If zero is not returned, then message could not be sent and caller should terminate connection.
	*/
	static int sendSocketMessage(SOCKET socket, std::string message);
	
	/*
	Initializes windows socket API.
	Include in main function before using WinSock:

	if (initializeWinSock() != 0) {
		return 1;
	}
	*/
	static int initializeWinSock();
	/*
		Takes a message split by a delimeter, and returns a vector of the strings without the delimeter.
	*/
	static std::vector<std::string> splitByDelimeter(std::string message, std::string delimeter);

	/*
		Will generate a random point within a rectangle (lowerBounds, upperBounds)
	*/
	static Point generateRandomPoint(Point lowerBounds, Point upperBounds);
};

#endif // !UTILITIES_H

