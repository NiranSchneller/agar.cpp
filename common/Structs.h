#ifndef STRUCTS_H
#define STRUCTS_H
#include <SFML/Graphics.hpp>

#include "Point.h"
#include <vector>
#include "Blob.h"
#include <memory>
struct ClientInformation {
	Point clientMousePosition;
}; // Information that will be sent from client to server

struct AgarServerInformation {
	std::vector<std::unique_ptr<Blob>> blobsToDraw; // Pass pointer because we don't want to copy objects lol
}; // Information will be sent from server -> client

#endif // !STRUCTS_H
