#ifndef BLOB_H
#define BLOB_H
#include <string>
#include <SFML/Graphics.hpp>
#include "Point.h"
class Blob {

protected:
	std::string name;
	double radius;
	Point position;
	sf::Color blobColor;
public:
	Blob(std::string name, double radius, Point position, sf::Color blobColor);
	Blob(double radius, Point position, sf::Color blobColor);
	Blob(double radius, Point position);
	~Blob() = default;

	std::string getBlobName();
	double getRadius();
	Point getPosition();
	sf::Color getColor();
	void setBlobName(std::string name);
	void setRadius(double radius);
	void setPosition(Point position);
	void setColor(sf::Color blobColor);
};

#endif // !BLOB_H
