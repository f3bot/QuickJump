#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"

class Game;

class Platform : public sf::RectangleShape
{
private:
	sf::Vector2f size;
	sf::Vector2f position;
	sf::RectangleShape rect;
	sf::Texture t;

	std::vector<sf::IntRect> textureVector;

	bool isDestroyed;
	bool isStanding;

public:
	Platform(float xPos, float yPos);
	Platform();
	~Platform();

	void animateDestruction();

	void drawTo(sf::RenderWindow& window);
	void playerBlockCollision(Player& player);


	float getPositionY();
	bool handleTexture();


	void moveUp(float verticalSpeed);
};

