#include "ServerClientThread.h"

ServerClientThread::ServerClientThread(SOCKET* socket) {
	this->socket = *socket;
	this->clientInformation = { {0,0} };
}

ClientInformation ServerClientThread::getClientInformation() {
	return this->clientInformation;
}

void ServerClientThread::handleClient() {
	// TODO: Fill!
}