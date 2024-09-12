#ifndef SERVER_H
#define SERVER_H
#include <vector>
#include "ServerClientThread.h"
class Server
{
private:
	std::vector<ServerClientThread> threads;
public:
	Server();
	void startServer(); // This will be an infinite loop which accepts clients

};


#endif // !SERVER_H

