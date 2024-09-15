#include <SFML/Graphics.hpp>
#include "Blob.h"
#include "Constants.h"
Blob::Blob(std::string name, double radius, Point position, sf::Color blobColor) {
	this->setBlobName(name);
	this->setRadius(radius);
	this->setPosition(position);
	this->setColor(blobColor);
}

Blob::Blob(double radius, Point position, sf::Color blobColor) {
	this->setRadius(radius);
	this->setPosition(position);
	this->setColor(blobColor);
}
Blob::Blob(double radius, Point position) {
	this->setRadius(radius);
	this->setPosition(position);
}
Blob::Blob() {
}

std::string Blob::getBlobName() {
	return this->name;
}

double Blob::getRadius() {
	return this->radius;
}

Point Blob::getPosition() {
	return this->position;
}
sf::Color Blob::getColor() {
	return this->blobColor;
}

void Blob::setBlobName(std::string name) {
	this->name = name;
}

void Blob::setRadius(double radius) {
	this->radius = radius;
}
void Blob::setPosition(Point position) {
	this->position = position;
}
void Blob::setColor(sf::Color blobColor) {
	this->blobColor = blobColor;
}

/*
	The blob's point is it's center.
	In SFML the circle's pos is TopLeft, which is radius+TITLE_BAR_SIZE.

	This is used on the client side to draw the actual blob on the screen.
*/
sf::CircleShape& Blob::blobToCircle() {

	sf::Vector2f pos(this->position.GetX() - this->radius, this->position.GetY() - this->radius - TITLE_BAR_SIZE);

	sf::CircleShape circle(this->radius);
	circle.setPosition(pos.x, pos.y);
	
	return circle;
}