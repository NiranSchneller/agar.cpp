#ifndef SERVER_H
#define SERVER_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <WinSock2.h>
#include <thread>
#include "Player.h"
#include "Point.h"
#include "PlayerCamera.h"
class Server
{
private:
	/*
		Unique pointers we want automatic memory management,
		and if we just made it of type std::thread everytime we pushed back
		a thread it would try to copy it. Using only vector of *thread would 
		result in us having to manually delete the threads.
	*/
	std::vector<std::unique_ptr<std::thread>> threads;
	std::vector<std::unique_ptr<Blob>> blobsInGame;
	void dispatchToServerThread(SOCKET clientSocket);
	void handleClient(SOCKET clientSocket);

public:
	Server(int amountOfBlobs);
	/*
	 This will be an infinite loop which accepts clients.
	 This also starts up WinSock API.
	*/
	int startServer(int port); 
	Player spawnPlayer();

	static std::vector<std::unique_ptr<Blob>> findWhichBlobsToDraw(std::vector<std::unique_ptr<Blob>>& blobsInGame,
		Player player,
		PlayerCamera camera);

	static Point generateRandomBlobPosition(int blobRadius);


	static std::vector<std::unique_ptr<Blob>> spawnBlobs(int amountOfBlobs);

	static std::unique_ptr<Blob> spawnBlob();
};


#endif // !SERVER_H

