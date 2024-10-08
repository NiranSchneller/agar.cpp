#include "Server.h"
#include "Utilities.h"
#include "Protocol.h"
#include "Player.h"
#include "Constants.h"
#include "PlayerCamera.h"
#include <ws2tcpip.h>
#include <string.h>
#include <thread>
#include <iostream>
#include <rpcdce.h>  // Contains the UuidCreate function
#include <iomanip>   // For formatting the UUID output
#include <memory>

Server::Server(int amountOfBlobs) {
	this->blobsInGame = std::move(spawnBlobs(amountOfBlobs));
}

int Server::startServer(int port) {
	if (Utilities::initializeWinSock() != 0) {
		return 1;
	}

	// Getting address information
	struct addrinfo* result = NULL, * ptr = NULL, hints;
	int iResult;
	ZeroMemory(&hints, sizeof(hints)); // Zero the whole hints memory block
	hints.ai_family = AF_INET; // Specify addr+port
	hints.ai_socktype = SOCK_STREAM; // Stream based protocol (Next line defines which one)
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;
	iResult = getaddrinfo(NULL, std::to_string(port).c_str(), &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	// Initialize ListeningSocket
	SOCKET listeningSocket = INVALID_SOCKET;
	listeningSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (listeningSocket == INVALID_SOCKET) {
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	//Bind
	iResult = bind(listeningSocket, result->ai_addr, (int) result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(listeningSocket);
		WSACleanup();
		return 1;
	}
	freeaddrinfo(result); // Address information no longer needed

	
	if (listen(listeningSocket, 4) == SOCKET_ERROR) { // Max 4 pending connections
		printf("Listen failed with error: %ld\n", WSAGetLastError());
		closesocket(listeningSocket);
		WSACleanup();
		return 1;
	}

	SOCKET clientSocket = INVALID_SOCKET;
	
	while (true) {
		clientSocket = accept(listeningSocket, NULL, NULL);
		if (clientSocket == INVALID_SOCKET) {
			printf("accept failed: %d\n", WSAGetLastError());
			continue;
		}
		printf("Connection accepted, dispatching to thread \n");
		dispatchToServerThread(clientSocket);
	}

	// Reference because we can't copy unique pointer (big shock!)
	for (std::unique_ptr<std::thread>& thread : this->threads) {
		thread->join();
	}

	printf("Bye bye!");
}

void Server::dispatchToServerThread(SOCKET clientSocket) {
	this->threads.push_back(std::make_unique<std::thread>([this, clientSocket]() {handleClient(clientSocket); }));

}

#pragma comment(lib, "Rpcrt4.lib")
Player Server::spawnPlayer() {
	Player player;
	
	std::string uuidName;

	UUID uuid;
	RPC_STATUS status = UuidCreate(&uuid);
	if (status == RPC_S_OK) {
		// Convert the UUID to a string
		RPC_CSTR uuidString;
		UuidToStringA(&uuid, &uuidString);
		// Output the UUID
		
		uuidName = std::string(reinterpret_cast<const char*>(uuidString));
		std::cout << "Generated UUID: " << uuidName << std::endl;

		// Free the string after use
		RpcStringFreeA(&uuidString);
	}
	else {
		std::cout << "Failed to generate UUID" << std::endl;
	}

	player.setBlobName(uuidName);
	player.setRadius(PLAYER_STARTING_RADIUS);
	player.setPosition(generateRandomBlobPosition((int)player.getRadius()));
	player.setColor(PLAYER_COLOR); // Black

	return player;
}

void Server::handleClient(SOCKET clientSocket) {
	// recieve first message from client
	std::string messageFromClient = Utilities::recieveSocketMessage(clientSocket);
	std::vector<int> initialInformation = Protocol::getInitialInformationFromClient(messageFromClient);
	printf("Recieved Initial information: W:%d, H:%d, TBP:%d", initialInformation.at(0),
		initialInformation.at(1), initialInformation.at(2));

	Player player = spawnPlayer();
	PlayerCamera camera(Point::Point(initialInformation.at(0), initialInformation.at(1)));

	/*
		Implement server side logic.
		Implement protocol.h
	*/
	Point clientMousePosition(0,0);
	auto lambda = [&camera]() {camera.run(); };
	std::thread cameraThread(lambda);
	while (true) {
		clientMousePosition = Protocol::getClientInformationFromClient(Utilities::recieveSocketMessage(clientSocket));
		
		player.calculateNewPlayerPosition(camera.worldToScreenCoordinates(player.getPosition(), player.getPosition()),
										clientMousePosition, PLAYER_VELOCITY);
		eatBlobs(player, camera, Point::Point(initialInformation.at(0), initialInformation.at(1)));
		camera.run();
		Utilities::sendSocketMessage(clientSocket, 
			Protocol::sendBlobToDrawToClient(Server::findWhichBlobsToDraw(this->blobsInGame, 
												player, camera)));
	}
	cameraThread.join();
}

/*
	Assumes the player radius will always be bigger than any of the blobs.
*/
void Server::eatBlobs(Player& player, PlayerCamera& camera, Point resolution) {

	double eatenBlobRadius;
	for (size_t i = 0; i < this->blobsInGame.size(); i++) {
		if (player.enclosesBlob(*this->blobsInGame.at(i))) {
			camera.ate(player.getRadius());
			player.ate(this->blobsInGame.at(i)->getRadius());
			this->blobMutex.lock();
			this->blobsInGame.erase(this->blobsInGame.begin() + i); // Remove Ith blob.
			this->blobsInGame.push_back(spawnBlob());
			this->blobMutex.unlock();
			i--;
		}
	}
}

/*
	Player position is in world coordinates
*/
std::vector<std::unique_ptr<Blob>> Server::findWhichBlobsToDraw(std::vector<std::unique_ptr<Blob>>& blobsInGame,
																Player player,
																PlayerCamera camera) {
	std::vector<std::unique_ptr<Blob>> blobsToDraw;
	Blob screenBlob;
	Point pos;
	int newRadius;
	Point playerPosition = player.getPosition();
	for (size_t i = 0; i < blobsInGame.size(); i++) {
		if (camera.shouldDrawBlobOnScreen(playerPosition, blobsInGame.at(i)->getPosition(), blobsInGame.at(i)->getRadius())) {
			screenBlob = Blob::Blob(blobsInGame[i]->getBlobName(), blobsInGame[i]->getRadius(), blobsInGame[i]->getPosition(), blobsInGame[i]->getColor());

			pos = camera.worldToScreenCoordinates(playerPosition, screenBlob.getPosition());
			pos = Point::Point((int)pos.GetX(), (int)pos.GetY());
			screenBlob.setPosition(pos);

			newRadius = camera.radiusWorldToScreen(screenBlob.getRadius());


			blobsToDraw.push_back(std::make_unique<Blob>(screenBlob.getBlobName(), newRadius, screenBlob.getPosition(), screenBlob.getColor()));
		}
	}

	if (blobsInGame.empty()) {
		printf("Player has no blobs to draw what? \n");
	}

	pos = camera.worldToScreenCoordinates(playerPosition, playerPosition);
	pos = Point::Point((int)pos.GetX(), (int)pos.GetY());
	newRadius = camera.radiusWorldToScreen(player.getRadius());
	blobsToDraw.push_back(std::make_unique<Blob>(player.getBlobName(), newRadius, pos, player.getColor()));

	return blobsToDraw;
}

Point Server::generateRandomBlobPosition(int blobRadius) {
	Point lowerBounds(blobRadius, blobRadius);
	Point upperBounds(MAP_SIZE - blobRadius, MAP_SIZE - blobRadius);
	return Utilities::generateRandomPoint(lowerBounds, upperBounds);
}


std::vector<std::unique_ptr<Blob>> Server::spawnBlobs(int amountOfBlobs) {
	std::vector<std::unique_ptr<Blob>> blobs;
	for (size_t i = 0; i < amountOfBlobs; i++) {
		blobs.push_back(Server::spawnBlob());
		std::cout << blobs[i]->getPosition().GetY() << std::endl;
	}
	return blobs;
}
sf::Color generateRandomColor() {
	Point random = Utilities::generateRandomPoint(Point::Point(0, 0), Point::Point(124, 124));
	return sf::Color(random.GetX(), random.GetY(), (random.GetX() + random.GetY()) / 2);
}

std::unique_ptr<Blob> Server::spawnBlob() {
	return std::make_unique<Blob>("", BLOB_RADIUS, Server::generateRandomBlobPosition(BLOB_RADIUS), generateRandomColor());
}

