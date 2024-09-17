#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Constants.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

Player::Player() {

}

void Player::calculateNewPlayerPosition(Point currentPlayerPosition, Point mousePosition, int velocity) {
    // Calculate angle between mouse and player
    Point delta(mousePosition.GetX() - currentPlayerPosition.GetX(), mousePosition.GetY() - currentPlayerPosition.GetY());
    long double angle = atan2(delta.GetY(), delta.GetX());
    Point toAdd(velocity * cos(angle), velocity * sin(angle));

    Point newPosition = this->position.plus(toAdd);

    if (newPosition.inRectangle(Point::Point(0, 0), Point::Point(MAP_SIZE, MAP_SIZE))) {
        this->setPosition(newPosition);
    }
}

bool Player::enclosesBlob(Blob& blob) {
    return this->getPosition().distance(blob.getPosition()) < this->radius + blob.getRadius();
}

void Player::ate(double radius) {
    double temp = this->radius;
    this->radius = std::sqrt((radius * radius) + (this->radius * this->radius));
}