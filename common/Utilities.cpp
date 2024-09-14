#include <SFML/Graphics.hpp>

#include "Utilities.h"
#include <string>
#include "Constants.h"
#include <memory>
const bool LOG_TCP = true;


int Utilities::sendSocketMessage(SOCKET socket, std::string message) {
	int iResult;
	int bytesSent = 0; // Shock!
	std::string remainingMessage;
	int remainingMessageLength;
	/*
		Send message size
	*/
	std::string messageLengthInString = std::to_string(message.length());
	std::string messageSize = messageLengthInString + DELIMETER;
	
	// SIZE_HEADER_SIZE - 1 - messageLengthInString.length() -> the amount of zeroes to append to the beginning of the string
	messageSize.insert(0, SIZE_HEADER_SIZE - 1 - messageLengthInString.length(), '0');

	if (bytesSent != SIZE_HEADER_SIZE) {
		iResult = send(socket, messageSize.c_str(), SIZE_HEADER_SIZE - bytesSent, 0);
		if (iResult == SOCKET_ERROR) {
			printf("send failed: %d\n", WSAGetLastError());
			return 1;
		}
		bytesSent += iResult;
	}


	/*
		Send actual message
	*/
	printf("Message length: %d \n", message.length());

	bytesSent = 0; // Shock!
	while (bytesSent < message.length()) {

		remainingMessageLength = message.length() - bytesSent;
		remainingMessage = message.substr(bytesSent, remainingMessageLength);

		iResult = send(socket, remainingMessage.c_str(), remainingMessageLength, 0);
		if (iResult == SOCKET_ERROR) {
			printf("send failed: %d \n", WSAGetLastError());
			return 1;
		}

		bytesSent += iResult;
	}


	if (LOG_TCP) {
		std::string finalMessage = messageSize + message;
		printf("Message sent successfully: %s \n", finalMessage.c_str());
	}
	return 0;
}



std::string Utilities::recieveSocketMessage(SOCKET socket) {
	/*
		Parse message size.
	*/
	int iResult;
	int bytesRecieved = 0;
	size_t sizeBufferSize = SIZE_HEADER_SIZE;
	 
	if (SIZE_HEADER_SIZE != 9) {
		printf("SIZE HEADER SIZE IS WRONG CHECK!!!! \n");
	}

	std::unique_ptr<char[]> sizeBuffer = std::make_unique<char[]>(sizeBufferSize);

	while (bytesRecieved != sizeBufferSize) {
		iResult = recv(socket, sizeBuffer.get(), sizeBufferSize, 0);

		if (iResult <= 0) {
			printf("Connection either closed or error! \n");
			return "SOCKET ERROR " + std::to_string(iResult);
		}
		bytesRecieved += iResult;
	}
	
	/*
		Size of message recieved, digest actual message....
	*/
	sizeBuffer.get()[8] = '\0'; // The delimeter is irrelevant, we want size
	int messageSize = std::stoi(sizeBuffer.get());
	bytesRecieved = 0;

	if (LOG_TCP) {
		printf("Recieved message length: %d \n", messageSize);
	}
	std::unique_ptr<char[]> messageBuffer = std::make_unique<char[]>(messageSize + 1); // + 1 because of \0 null termination (it was very annoying to figure this one out)

	while (bytesRecieved < messageSize) {
		iResult = recv(socket, messageBuffer.get(), messageSize, 0);

		if (iResult <= 0) {
			printf("Connection either closed or error! \n");
			return "SOCKET ERROR " + std::to_string(iResult);
		}

		bytesRecieved += iResult;
	}
	std::string message(messageBuffer.get());

	if (LOG_TCP) {
		printf("Message recieved: %s \n", message.c_str());
		printf("Bytes recieved: %d \n", bytesRecieved);
	}
	return message;
}

std::vector<std::string> Utilities::splitByDelimeter(std::string message, std::string delimeter) {
	std::vector<std::string> out;
	int currentIndex = message.find(delimeter);
	
	while (currentIndex != std::string::npos) {
		out.push_back(message.substr(0, currentIndex));
		message = message.substr(currentIndex + delimeter.length());
		currentIndex = message.find(delimeter);
	}
	out.push_back(message.substr(0, currentIndex));
	return out;
}

int Utilities::initializeWinSock() {
	WSADATA wsaData;
	int iResult;
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d \n", iResult);
	}
	return iResult;
}
