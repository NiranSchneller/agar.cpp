#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <SFML/Graphics.hpp>

#include <string>
int calculateTitleBarSize();
extern const int TITLE_BAR_SIZE; // The size of the title bar at the top of the window
extern const std::string DELIMETER;
extern const std::string SIZE_HEADER; // 8 characters for length and one delimeter
extern const int SIZE_HEADER_SIZE;
extern const int MAP_SIZE;
extern const int BLOB_RADIUS;
extern const int PLAYER_STARTING_RADIUS;
extern const int BLOB_AMOUNT;
extern const double PLAYER_VELOCITY; // Pixels per frame

#endif // !CONSTANTS_H
