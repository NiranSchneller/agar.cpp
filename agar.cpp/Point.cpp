#include "Point.h"

Point::Point(double x = 0, double y = 0) {
	this->x = x;
	this->y = y;
}

double Point::GetX() {
	return this->x;
}

double Point::GetY() {
	return this->y;
}

void Point::SetX(double x) {
	this->x = x;
}

void Point::SetY(double y) {
	this->y = y;
}

