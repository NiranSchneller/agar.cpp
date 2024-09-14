#pragma comment(lib,"WS2_32")
#include "Server.h"

int main(int argc, char* argv[]) {
	Server agarServer(1);
	agarServer.startServer(8723);
	return 0; 
}