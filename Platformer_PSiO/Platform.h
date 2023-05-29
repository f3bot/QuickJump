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

	float animationTime;
	int animationState;

	int selected;

public:
	Platform(float xPos, float yPos);
	Platform();
	~Platform();

	void setDestruction(float dt);

	void drawTo(sf::RenderWindow& window);
	void playerBlockCollision(Player& player);


	float getPositionY();
	float getPositionX();

	float getGlobalBoundsTop();

	bool handleTexture();

	int getAnimationState();

	int setSelected(int s);
	void setTextures();


	void moveUp(float verticalSpeed);
};

