#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <time.h>
#include <ctime>
#include "Player.h"
#include "Platform.h"

class Coin :public sf::Sprite 
{
private:
	sf::Vector2f position;

	sf::Texture coinTexture;
	std::vector<sf::IntRect> textureVector;

	int score;
	sf::Font font;
	sf::Text scoreText;

	float animationTime;
	int animationState;

	bool randomFloatFound;

	float randomX;

public:
	Coin(Platform *plat);
	void changePosition(Platform *platform, Player& player);
	void collideWithPlayer(Player& player);
	bool handleTexture();
	void animateCoin(float dt);

	void updateText();

	float randomFloat(float min, float max);

	void updateCoin(Player& player, sf::RenderWindow& window,float dt, Platform *platform);
};

