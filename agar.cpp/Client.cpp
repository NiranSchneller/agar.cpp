#include "PlayerClient.h"
#include <WinSock2.h>
#include <ws2tcpip.h>
#include "PlayerClient.h"

#pragma comment(lib,"WS2_32")
/*
	Initializes windows socket API.
	Include in main function before using WinSock:
	
	if (initializeWinSock() != 0) {
		return 1;
	}
*/
int initializeWinSock();

int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("You have to specify which ip and port you want to connect to! Exiting program...");
		return 1;
	}
	if (initializeWinSock() != 0) {
		return 1;
	}
	
	struct addrinfo* result = NULL,
		* ptr = NULL,
		hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET; // Specify addr+port
	hints.ai_socktype = SOCK_STREAM; // Stream based protocol (Next line defines which one)
	hints.ai_protocol = IPPROTO_TCP;
	
	// Get address information from API
	int iResult = getaddrinfo(argv[1], argv[2], &hints, &result);
	printf("Nice");
	PlayerClient client(result);
	int connectionResult = client.connectToServer();
	if (connectionResult != 0) {
		return 1;
	}

	return 0;
}

int initializeWinSock() {
	WSADATA wsaData;
	int iResult;
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d \n", iResult);
	}
	return iResult;

}