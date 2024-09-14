#ifndef PLAYER_CLIENT_H
#define PLAYER_CLIENT_H
#include <SFML/Graphics.hpp>
#include <winsock2.h>
#include <WS2tcpip.h>
#include "Structs.h"
#include <mutex>
class PlayerClient
{
private:
	SOCKET playerSocket;
	AgarServerInformation updatedInformation;
	addrinfo* connectionInformation;
	int screenWidth;
	int screenHeight;
	int titleBarSize;

	/*
		While we update new information from server we can't have the owner trying to use getUpdatedInformation()
	*/
	std::mutex updateInformationMutex; 
public:
	PlayerClient(addrinfo* connectionInformation, int screenWidth, int screenHeight, int titleBarSize); // Assumes WinSock has already gone through startup
	AgarServerInformation getUpdatedInformation();

	/*
		Attempts connecting to server using address information given at constructor.
		If a nonzero value is returned, then the connection has failed.
	*/
	int connectToServer();
	/*
		Should be seperated into a different thread by owner.
		Will attempt to open a connection to said ip address and port, if successfull will start communicating.
		If not, returns.
	*/
	int handleConnection(); 
};


#endif // !PLAYER_CLIENT_H


