#ifndef PLAYER_CAMERA_H
#define PLAYER_CAMERA_H

#include "Point.h"
#include "Interpolator.h"
class PlayerCamera
{
private:

	Point cameraDimensions;
	Point screenResolution; // x -> Width, y -> Height
	Interpolator widthInterpolator;
	Interpolator heightInterpolator;
public:
	PlayerCamera(Point screenResolution);

	/*
		Converts a point from world coordinates to screen coordinates
		playerPosition is in world coordinates
	*/
	Point worldToScreenCoordinates(Point playerPosition, Point worldPoint);

	int radiusWorldToScreen(double radius);

	/*
		
	*/
	bool shouldDrawBlobOnScreen(Point playerPosition, Point blobPosition, double blobRadius);
	
	/*
		Once the player has eaten a blob (whether it's a player or a regular blob),
		this function should be called.
	*/
	void ate(double playerRadius);

	// Should be ran every loop
	void run();
};

#endif
