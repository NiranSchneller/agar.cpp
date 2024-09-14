#ifndef STRUCTS_H
#define STRUCTS_H
#include "Point.h"
#include <vector>
#include "Blob.h"
struct ClientInformation {
	Point clientMousePosition;
}; // Information that will be sent from client to server

struct AgarServerInformation {
	std::vector<Blob*> blobsToDraw; // Pass pointer because we don't want to copy objects lol
}; // Information will be sent from server -> client

#endif // !STRUCTS_H
