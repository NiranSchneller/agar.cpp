#include <SFML/Graphics.hpp>
#include "Player.h"

Player::Player() {

}

void Player::calculateNewPlayerPosition(Point currentPlayerPosition, Point mousePosition, int velocity) {
    // Calculate angle between mouse and player
    Point delta(mousePosition.GetX() - currentPlayerPosition.GetX(), mousePosition.GetY() - currentPlayerPosition.GetX());
    long double angle = atan2(delta.GetY(), delta.GetX());
    
    Point newPosition (this->position.GetX() + (velocity * cos(angle)), this->position.GetY() + (velocity * sin(angle)));
    this->setPosition(newPosition);
}