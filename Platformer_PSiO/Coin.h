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

	sf::Vector2f updatedPosition;

	sf::Texture coinTexture;
	std::vector<sf::IntRect> textureVector;

	sf::Sprite coinSprite;

	int score;
	sf::Font font;
	sf::Text scoreText;

	float animationTime;
	int animationState;

	bool pickedUp;

	bool coinsSpawned;


	bool isDeleted;


	bool randomIntFound;
	int r;

	float randomX;



	int platformIndex;
public:
	Coin(Player& player, Platform* plat);
	Coin(Platform* plat);
	void changePosition(Platform *platform, Player& player, std::vector<Platform*> platVec);
	bool collideWithPlayer(Player& player);
	bool handleTexture();
	void animateCoin(float dt);

	int randomInt(int max);

	bool checkDeleted(std::vector<Platform*> platVec, Platform* plat);

	int getScore() {
		return score;
	}

	float randomFloat(float min, float max);

	void handleCoinsPowerUp(Player& player, Platform* plat);

	void updateCoin(Player& player, sf::RenderWindow& window,float dt, Platform *platform, std::vector<Platform*> platVec);
};

