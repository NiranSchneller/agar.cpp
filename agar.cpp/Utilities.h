#ifndef UTILITIES_H
#define UTILITIES_H
#include <string>
#include <winsock.h>
// TODO: create the implementations
class Utilities
{
	static std::string recieveSocketMessage(SOCKET* socket);
	static void sendSocketMessage(SOCKET* socket, std::string message);

};

#endif // !UTILITIES_H

