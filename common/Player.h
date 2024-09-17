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

	/*
		The purpose of this function is to check if the player should eat the blob
	*/
	bool enclosesBlob(Blob& blob);

	void ate(double radius);
};

#endif // !PLAYER_H


