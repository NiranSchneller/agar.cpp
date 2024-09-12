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
