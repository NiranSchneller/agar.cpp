#ifndef PLAYER_CAMERA_H
#define PLAYER_CAMERA_H

#include "Point.h"
class PlayerCamera
{
private:

	Point cameraDimensions;
	Point screenResolution; // x -> Width, y -> Height
public:
	PlayerCamera(Point screenResolution);

	/*
		Converts a point from world coordinates to screen coordinates
		playerPosition is in world coordinates
	*/
	Point worldToScreenCoordinates(Point playerPosition, Point worldPoint);

	/*
		
	*/
	bool shouldDrawBlobOnScreen(Point playerPosition, Point blobPosition);
};

#endif
