#include "PlayerClient.h"
#include "Utilities.h"
#include "Constants.h"
#include "Graphics.h"
#include <thread>
#include <functional> // For std::bind
#include <chrono>
#include <WinSock2.h>
#include <ws2tcpip.h>
#pragma comment(lib,"WS2_32")

int screenWidth = 1280;
int screenHeight = 720;
int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("You have to specify which ip and port you want to connect to! Exiting program...");
		return 1;
	}
	if (Utilities::initializeWinSock() != 0) {
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
	printf("IP: %s, port: %s \n", argv[1], argv[2]);
	int iResult = getaddrinfo(argv[1], argv[2], &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	PlayerClient client(result, screenWidth, screenHeight, TITLE_BAR_SIZE);
	int connectionResult = 0;
	int* pConnectionResult = &connectionResult;
	Graphics graphics(screenWidth, screenHeight);
	std::thread clientThread(std::bind(&PlayerClient::connectToServer, std::ref(client), pConnectionResult, &graphics.getGameWindow()));
	
	AgarServerInformation serverInfo;
	std::chrono::milliseconds delay(10);
	while (!client.isFinished()) {
		serverInfo = client.getUpdatedInformation();
		graphics.getGameWindow().clear(BACKGROUND_COLOR); 
		graphics.drawAllBlobs(serverInfo.blobsToDraw);
		graphics.getGameWindow().display();
		
		if (*pConnectionResult != 0) {
			return 1;
		}
		std::this_thread::sleep_for(delay);
	}
	

	WSACleanup();
	return 0;
}

