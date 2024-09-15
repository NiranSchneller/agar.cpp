#include <SFML/Graphics.hpp>
#include "PlayerClient.h"
#include "Utilities.h"
#include "Protocol.h"

PlayerClient::PlayerClient(addrinfo* connectionInformation, int screenWidth, int screenHeight, int titleBarSize) {
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	this->titleBarSize = titleBarSize;
	this->finished = false;

	this->connectionInformation = connectionInformation;
	this->playerSocket = INVALID_SOCKET;
	this->pGameWindow = nullptr;
}

void PlayerClient::connectToServer(int *connectionResult, sf::RenderWindow* gameWindow) {
	int iResult;
	this->pGameWindow = gameWindow;
	this->playerSocket = socket(this->connectionInformation->ai_family,
								this->connectionInformation->ai_socktype,
								this->connectionInformation->ai_protocol);
	if (this->playerSocket == INVALID_SOCKET) { // Connection failed (Big L)
		printf("Error at socket(), %ld \n", WSAGetLastError());
		freeaddrinfo(this->connectionInformation);
		*connectionResult = 1;
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
		*connectionResult = handleConnection();
	}
	else {
		printf("All possible addresses have been exhausted, no viable connection found!, Exiting.... \n");
		*connectionResult = 1;
	}
	this->finished = true;
}

int PlayerClient::handleConnection() {
	bool running = true;
	int exitCode = 0;
	// Send server first message With information (screen resolution, title bar pixels)
	// Recieve confirmation message from server
	int returnCode = Utilities::sendSocketMessage(this->playerSocket,
				Protocol::sendInitialInformationToServer(this->screenWidth, this->screenHeight, this->titleBarSize));

	if (returnCode != 0) {
		printf("Error sending initial message!");
		return 1;
	}

	POINT cursorPosition = { 0,0 };
	Point mousePosition(0,0);
	Point gameWindowPos(0,0);
	std::vector<std::unique_ptr<Blob>> blobsToDraw;
	std::string recievedMessage;
	while (running) {
		GetCursorPos(&cursorPosition);

		// Window relative cursor position.
		mousePosition.SetX(cursorPosition.x - this->pGameWindow->getPosition().x);
		mousePosition.SetY(cursorPosition.y - this->pGameWindow->getPosition().y);

		returnCode = Utilities::sendSocketMessage(this->playerSocket, Protocol::sendClientInformationToServer(mousePosition));

		if (returnCode != 0) {
			return 1;
		}

		recievedMessage = Utilities::recieveSocketMessage(this->playerSocket);

		if (recievedMessage.find("SOCKET ERROR") != std::string::npos) {
			return 1;
		}

		// Should be abstracted in protocol class but that would be hard
		if (recievedMessage.find("KILLED") != std::string::npos) {
			this->finished = true;
			return 0;
		}
		
		blobsToDraw = std::move(Protocol::getBlobsToDrawFromServer(recievedMessage));

		this->updateInformationMutex.lock();
		updatedInformation.blobsToDraw = std::move(blobsToDraw);
		this->updateInformationMutex.unlock();
	}
	this->finished = true;
	return exitCode;

	// Check out
}


bool PlayerClient::isFinished() {
	return this->finished;
}

AgarServerInformation PlayerClient::getUpdatedInformation() {
	AgarServerInformation serverInformation;
	
	this->updateInformationMutex.lock();
	serverInformation.blobsToDraw = std::move(updatedInformation.blobsToDraw);
	this->updateInformationMutex.unlock();

	return serverInformation;

}
