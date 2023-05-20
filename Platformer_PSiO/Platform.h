#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
class Platform : public sf::RectangleShape
{
private:
	sf::Vector2f size;
	sf::Vector2f position;
	sf::RectangleShape* rect;
	sf::Texture t;
public:
	Platform();
	~Platform();
	void drawTo(sf::RenderWindow& window);
	void playerBlockCollision(Player& player);
	void checkForFalling(Player& player);
	bool handleTexture();
	void generateWorld(std::vector<Platform> platVec);
};

