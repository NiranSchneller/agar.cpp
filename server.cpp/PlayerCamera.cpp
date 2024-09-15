#include "PlayerCamera.h"

PlayerCamera::PlayerCamera(Point screenResolution) {
	this->width = screenResolution.GetX();
	this->height = screenResolution.GetY();
	this->screenResolution = screenResolution;
}

Point PlayerCamera::worldToScreenCoordinates(Point playerPosition, Point worldPoint) {
	// Calculate PlayerCamera position
	Point playerCameraPosition;
	playerCameraPosition.SetX(playerPosition.GetX() - this->width / 2);
	playerCameraPosition.SetY(playerPosition.GetY() - this->height / 2);

	Point relativeToPlayerCamera = worldPoint.minus(playerCameraPosition);

	return relativeToPlayerCamera.mul(this->screenResolution.div(Point::Point(this->width, this->height)));
}