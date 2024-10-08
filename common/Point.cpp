#include <SFML/Graphics.hpp>
#include "Point.h"
#include <cmath>

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

Point Point::minus(Point other) {
	return Point::Point(this->x - other.x, this->y - other.y);
}

Point Point::plus(Point other) {
	return Point::Point(this->x + other.x, this->y + other.y);
}

Point Point::mul(Point other) {
	return Point::Point(this->x * other.x, this->y * other.y);
}

Point Point::div(Point other) {
	return Point::Point(this->x / other.x, this->y / other.y);
}

bool Point::inRectangle(Point topLeft, Point bottomRight) {
	return (this->x - topLeft.x) > 0 && (this->y - topLeft.y) > 0
		&& (bottomRight.x - this->x) > 0 && (bottomRight.y - this->y) > 0;
}

Point Point::square() {
	return this->mul(*this);
}

double Point::distance(Point other) {
	Point cartesian = other.minus(*this).square();

	return std::sqrt(cartesian.x + cartesian.y);
}

