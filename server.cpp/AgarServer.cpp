#pragma comment(lib,"WS2_32")
#include "Server.h"
#include "Constants.h"
int main(int argc, char* argv[]) {
	Server agarServer(BLOB_AMOUNT);
	agarServer.startServer(8723);
	return 0; 
}