#ifndef UTILITIES_H
#define UTILITIES_H
#include <string>
#include <WinSock2.h>
// TODO: create the implementations
class Utilities
{
public:
	static std::string recieveSocketMessage(SOCKET* socket);
	static void sendSocketMessage(SOCKET* socket, std::string message);
	/*
	Initializes windows socket API.
	Include in main function before using WinSock:

	if (initializeWinSock() != 0) {
		return 1;
	}
	*/
	static int initializeWinSock();
};

#endif // !UTILITIES_H

