#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "Constants.h"

int calculateTitleBarSize() {
    HWND hwnd = GetConsoleWindow(); // Get the handle to the console window
    RECT windowRect, clientRect;
    GetWindowRect(hwnd, &windowRect); // Get the window size
    GetClientRect(hwnd, &clientRect); // Get the client area size
    int titleBarHeight = (windowRect.bottom - windowRect.top) - (clientRect.bottom - clientRect.top);
    return titleBarHeight;
}
const int TITLE_BAR_SIZE = calculateTitleBarSize();
const std::string DELIMETER = "~";
const std::string SIZE_HEADER = "00000000" + DELIMETER; // 8 characters for length and one delimeter
const int SIZE_HEADER_SIZE = SIZE_HEADER.length();
const int MAP_SIZE = 20000;
const int BLOB_RADIUS = 20;
const sf::Color BACKGROUND_COLOR = sf::Color::Color(173, 216, 230);
const sf::Color PLAYER_COLOR = sf::Color(0, 200, 200);
const int BLOB_AMOUNT = 4000;
const double INTERPOLATION_STEP = 0.01;
const int PLAYER_STARTING_RADIUS = 100;
const double PLAYER_VELOCITY = 1;

