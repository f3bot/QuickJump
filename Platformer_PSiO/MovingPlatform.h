#pragma once
#include <SFML/Graphics.hpp>
#include "Platform.h"
#include <iostream>

class MovingPlatform : public Platform
{
private:
	bool playerPlatformContact;
	sf::Vector2f movingPlatPosition;

	sf::RectangleShape movingRect;
public:
	void moveHorizontally(Player& player);
	void movingPlatformCollision(Player& player);
	MovingPlatform(float xPos, float yPos);
	void DrawTo(sf::RenderWindow& window);
	void debug();
};
