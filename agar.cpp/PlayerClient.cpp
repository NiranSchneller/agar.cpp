#include "PlayerClient.h"
PlayerClient::PlayerClient(addrinfo* connectionInformation) {
	this->connectionInformation = connectionInformation;
	this->playerSocket = INVALID_SOCKET;
}

int PlayerClient::connectToServer() {
	this->playerSocket = socket(this->connectionInformation->ai_family,
								this->connectionInformation->ai_socktype,
								this->connectionInformation->ai_protocol);
	if (this->playerSocket == INVALID_SOCKET) { // Connection failed (Big L)
		printf("Error trying to connect to server using socket(), %ld \n", WSAGetLastError());
		freeaddrinfo(this->connectionInformation);
		WSACleanup();
		return 1;
	}
	return 0;
}

int PlayerClient::handleConnection() {
	bool running = true;
	int exitCode = 0;
	// Send server first message With information (screen resolution, title bar pixels)
	// Recieve confirmation message from server

	while (running) {
		// Send server mouse position relative to window
		// Recieve information (all blobs to draw on screen)
		
		// If killed message then exit and womp womp (exit code 0)
		// If socket error then exit with exit code 1 
		
		// Store in information variable
	}
	return exitCode;

	// Check out
}