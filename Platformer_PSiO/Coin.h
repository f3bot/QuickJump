#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"

class Coin :public sf::Sprite 
{
private:
	sf::Vector2f position;

	sf::Texture coinTexture;
	std::vector<sf::IntRect> textureVector;

	int score;
	sf::Text scoreText;

	float animationTime;
	int animationState;

public:
	Coin();
	void changePosition();
	void collideWithPlayer(Player& player);
	bool handleTexture();
	void animateCoin(float dt);

	void updateCoin(Player& player, sf::RenderWindow& window,float dt);
};

