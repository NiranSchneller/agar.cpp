#include "PlayerCamera.h"

PlayerCamera::PlayerCamera(Point screenResolution) {
	this->cameraDimensions.SetX(screenResolution.GetX());
	this->cameraDimensions.SetY(screenResolution.GetY());
	this->screenResolution = screenResolution;
}

Point PlayerCamera::worldToScreenCoordinates(Point playerPosition, Point worldPoint) {
	// Calculate PlayerCamera position
	Point playerCameraPosition = playerPosition.minus(this->cameraDimensions.div(Point::Point(2,2)));

	Point relativeToPlayerCamera = worldPoint.minus(playerCameraPosition);

	return relativeToPlayerCamera.mul(this->screenResolution.div(this->cameraDimensions));
}

bool PlayerCamera::shouldDrawBlobOnScreen(Point playerPosition, Point blobPosition) {
	return blobPosition.inRectangle(playerPosition.minus(this->cameraDimensions.div(Point::Point(2, 2))),
		playerPosition.plus(this->cameraDimensions.div(Point::Point(2, 2))));
}