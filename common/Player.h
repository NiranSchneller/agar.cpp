#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>

#include "Blob.h"
class Player : public Blob
{
public:
	Player();
	/*
		Updates position member variable.

		currentPlayerPosition and mousePosition are relative to the game WINDOW.
	*/
	void calculateNewPlayerPosition(Point currentPlayerPosition, Point mousePosition, int velocity);

};

#endif // !PLAYER_H


