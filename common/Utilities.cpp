#include "Utilities.h"

int Utilities::initializeWinSock() {
	WSADATA wsaData;
	int iResult;
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d \n", iResult);
	}
	return iResult;
}