#include "PlayerClient.h"
PlayerClient::PlayerClient(addrinfo* connectionInformation) {
	this->connectionInformation = connectionInformation;
	this->playerSocket = INVALID_SOCKET;
}

int PlayerClient::connectToServer() {
	int iResult;
	this->playerSocket = socket(this->connectionInformation->ai_family,
								this->connectionInformation->ai_socktype,
								this->connectionInformation->ai_protocol);
	if (this->playerSocket == INVALID_SOCKET) { // Connection failed (Big L)
		printf("Error at socket(), %ld \n", WSAGetLastError());
		freeaddrinfo(this->connectionInformation);
		return 1;
	}
	
	addrinfo* info = this->connectionInformation;
	// Loop through all possible addresses until we find one that is good
	while (info != NULL) {
		iResult = connect(this->playerSocket, info->ai_addr, (int)info->ai_addrlen);
		if (iResult != SOCKET_ERROR) {
			break;
		}
		info = info->ai_next;
	}

	if (info != NULL) {
		printf("Connection to server established! \n");
		return handleConnection();
	}

	printf("All possible addresses have been exhausted, no viable connection found!, Exiting.... \n");
	return 1;
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