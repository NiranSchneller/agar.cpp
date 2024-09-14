#ifndef PROTOCOL_H
#define PROTOCOL_H
#include <vector>
#include <string>
#include "Blob.h"
#include "Point.h"

/*
	In every function, the message param is the raw message recieved through socket connection,
	not including the size header and delimeter.
*/
class Protocol
{
public:
	/*
		From client to server.
	*/
	// One shot message 
	static std::string sendInitialInformationToServer(int resWidth, int resHeight, int titleBarSize);
	static std::vector<int> getInitialInformationFromClient(std::string message);

	// Client will send this periodically
	static std::string sendClientInformationToServer(Point mousePosition);
	static Point getClientInformationFromClient(std::string message);


	/*
		From server to client.
	*/
	// A list of blobs that the client will draw on screen.
	static std::string sendBlobToDrawToClient(std::vector<Blob>& blobsToDraw);
	// Reverse of sendBlobToDrawToClient, will convert from string back to list.
	static std::vector<Blob>& getBlobsToDrawFromServer(std::string message);

};

#endif

