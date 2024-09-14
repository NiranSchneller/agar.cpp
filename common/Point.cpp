#include <SFML/Graphics.hpp>
#include "Point.h"

Point::Point(double x, double y) {
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

