#include "Blob.h"

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