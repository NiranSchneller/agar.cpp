#ifndef SERVER_CLIENT_THREAD_H
#define SERVER_CLIENT_THREAD_H
#include <SFML/Graphics.hpp>
#include <WinSock2.h>

/*
	Each instance of this class is supposed to be in a thread of it's own. Will be dispatched by owner.
*/
class ServerClientThread
{
private:
	void handleClient();
protected:
	SOCKET socket;
	ClientInformation clientInformation;

public:
	ServerClientThread(SOCKET* socket);
	ClientInformation getClientInformation();


	~ServerClientThread() = default;
};

#endif // !SERVER_CLIENT_THREAD_H

