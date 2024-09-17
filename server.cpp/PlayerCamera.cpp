#include "PlayerCamera.h"
#include "Constants.h"

PlayerCamera::PlayerCamera(Point screenResolution) {
	this->cameraDimensions.SetX(screenResolution.GetX());
	this->cameraDimensions.SetY(screenResolution.GetY());
	this->screenResolution = screenResolution;
	this->widthInterpolator = Interpolator(INTERPOLATION_STEP, screenResolution.GetX());
	this->heightInterpolator = Interpolator(INTERPOLATION_STEP, screenResolution.GetY());
}

Point PlayerCamera::worldToScreenCoordinates(Point playerPosition, Point worldPoint) {
	// Calculate PlayerCamera position
	Point playerCameraPosition = playerPosition.minus(this->cameraDimensions.div(Point::Point(2,2)));

	Point relativeToPlayerCamera = worldPoint.minus(playerCameraPosition);

	return relativeToPlayerCamera.mul(this->screenResolution.div(this->cameraDimensions));
}

int PlayerCamera::radiusWorldToScreen(double radius) {
	return (int)(radius * (this->screenResolution.GetX() / this->cameraDimensions.GetX()));
}

bool PlayerCamera::shouldDrawBlobOnScreen(Point playerPosition, Point blobPosition, double blobRadius) {

	Point radius(2 * blobRadius, 2 * blobRadius);

	Point topLeft = playerPosition.minus(this->cameraDimensions.div(Point::Point(2, 2))).minus(radius);
	Point bottomRight = playerPosition.plus(this->cameraDimensions.div(Point::Point(2, 2))).plus(radius);
	return blobPosition.inRectangle(topLeft, bottomRight);
}

void PlayerCamera::ate(double playerRadius) {
	double scalar = playerRadius / PLAYER_STARTING_RADIUS;
	Point newCameraDimensions = this->screenResolution.mul(Point(scalar, scalar));
	newCameraDimensions.SetX((int) newCameraDimensions.GetX());
	newCameraDimensions.SetY((int)newCameraDimensions.GetY());
	printf("Scalar: %f \n", scalar);

	this->widthInterpolator.initializeInterpolation(this->cameraDimensions.GetX(), newCameraDimensions.GetX());
	this->heightInterpolator.initializeInterpolation(this->cameraDimensions.GetY(), newCameraDimensions.GetY());
}

void PlayerCamera::run() {
	this->cameraDimensions.SetX(this->widthInterpolator.interpolate());
	this->cameraDimensions.SetY(this->heightInterpolator.interpolate());
	printf("X: %f, Y: %f \n", this->cameraDimensions.GetX(), this->cameraDimensions.GetY());
}