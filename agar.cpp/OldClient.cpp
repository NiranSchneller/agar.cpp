/*#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <winuser.h>
#include <windef.h>
#include "Constants.h"
#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>

POINT screenToWindow(POINT* screenPos, POINT* windowPos);
POINT getCircleCenter(sf::CircleShape* circle);
POINT getCircleTopLeft(POINT* center, sf::CircleShape* circle);

/*
*     Returns the new position of the center of the circle using circle velocity
    POINT calculateNewCirclePosition(POINT* currentCenterPosition, POINT* mousePosition, long double velocity);


int main()
{
    std::chrono::milliseconds delay(20);

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
    sf::CircleShape circle(100.f);
    sf::RectangleShape rectangle(sf::Vector2f(120, 50));
    POINT cursorPosition = { 0,0 }, windowPosition = { 0,0 }, newCircleCenterPosition = { 0,0 }, circleCenter = { 0,0 }, newCirclePosition = { 0, 0 };
    POINT cursorWindowPosition = { 0,0 };
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        windowPosition = { window.getPosition().x, window.getPosition().y };
        GetCursorPos(&cursorPosition);
        cursorWindowPosition = screenToWindow(&cursorPosition, &windowPosition);
        circleCenter = getCircleCenter(&circle);
        
        //newCircleCenterPosition = calculateNewCirclePosition(&circleCenter, &cursorWindowPosition, 20);

        newCirclePosition = getCircleTopLeft(&newCircleCenterPosition, &circle);
        std::cout << "new CirclePosition X" << newCirclePosition.x << std::endl;
        std::cout << "old circle x: " << circle.getPosition().x << std::endl;
        circle.setPosition(newCirclePosition.x, newCirclePosition.y);
        std::cout << "new circle x: " << circle.getPosition().x << std::endl;
        std::cout << "X: " << newCirclePosition.x << " Y: " << newCirclePosition.y << std::endl;
        
        
        window.clear();
        window.draw(circle);
        window.display();
        std::this_thread::sleep_for(delay);
    }

    return 0;
}

POINT screenToWindow(POINT* screenPos, POINT* windowPos) {
    POINT windowPoint = { screenPos->x - windowPos->x, screenPos->y - windowPos->y };
    return windowPoint;
}

POINT getCircleCenter(sf::CircleShape* circle) {
    sf::Vector2<float> topLeftPosition = circle->getPosition();
    POINT center = { topLeftPosition.x + circle->getRadius(), topLeftPosition.y + TITLE_BAR_SIZE + circle->getRadius() };
    return center;
}

POINT getCircleTopLeft(POINT* center, sf::CircleShape* circle) {
    sf::Vector2<float> topLeftPosition = { center->x - circle->getRadius(), center->y - TITLE_BAR_SIZE - circle->getRadius() };
    POINT topLeft = { topLeftPosition.x, topLeftPosition.y };
    return topLeft;
}
*/

/*
    Calculates new position by adding cartesian factors of velocity using the angle between mouse and circle
POINT calculateNewCirclePosition(POINT* currentCenterPosition, POINT* mousePosition, long double velocity) {
    std::cout << "Mouse X: " << mousePosition->x << " Mouse Y: " << mousePosition->y << std::endl;
    std::cout << "currentCenterPosition X: " << currentCenterPosition->x << " currentCenterPosition Y: " << currentCenterPosition ->y << std::endl;

    POINT delta = { mousePosition->x - currentCenterPosition->x, mousePosition->y - currentCenterPosition->y };
    
    long double angle = atan2(delta.y, delta.x);
    std::cout << "Angle between mouse and circle: " << angle << std::endl;
    POINT newCenter = { currentCenterPosition->x + ( velocity * cos(angle) ), currentCenterPosition->y + (velocity * sin(angle))};
    
    POINT diff = { newCenter.x - currentCenterPosition->x, newCenter.y - currentCenterPosition->y };

    std::cout << "DIff X: " << diff.x << std::endl;
    return newCenter;
}
*/