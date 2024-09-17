#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Constants.h"
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