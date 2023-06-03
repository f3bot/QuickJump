#pragma once
#include "Player.h"
#include "Coin.h"
#include <random>
#include <ctime>
#include <time.h>
class PowerUp
{
public:
	virtual bool collideWithPlayer(Player& player) const = 0;
	virtual void setAttribute(Player& player) = 0;
	sf::Vector2f generatePosition(Player& player, sf::RenderWindow& window);
	bool checkScore(Coin& coin);
};

