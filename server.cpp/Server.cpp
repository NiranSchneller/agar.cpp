#include "Server.h"
#include "Utilities.h"
#include "Protocol.h"
#include <ws2tcpip.h>
#include <string.h>
#include <thread>
Server::Server(int i) {
	
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


void Server::handleClient(SOCKET clientSocket) {
	// recieve first message from client
	std::string messageFromClient = Utilities::recieveSocketMessage(clientSocket);
	std::vector<int> initialInformation = Protocol::getInitialInformationFromClient(messageFromClient);
	printf("Recieved Initial information: W:%d, H:%d, TBP:%d", initialInformation.at(0),
		initialInformation.at(1), initialInformation.at(2));

	/*
		Implement server side logic.
		Implement protocol.h
	*/
	while (true) {

	}
}