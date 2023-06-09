#include <SFML/Graphics.hpp>
#include "PowerUpJump.h"

PowerUpJump::PowerUpJump(Player& player, sf::RenderWindow& window) : sf::Sprite()
{
	if (!t.loadFromFile("assets/jump_power.png")) {
		std::cerr << "Nie wczytano tekstury grziba\n";
	}

	setTexture(t);
	position = generatePosition(player, window);
	setScale({ 2,2 });
	setPosition(position);

	std::cout << position.x << " " << position.y << std::endl;
	isDeleted = false;
}

void PowerUpJump::setAttribute(Player& player)
{
	if (collideWithPlayer(player)) {
		player.setPowerJumped(true);
		player.setCounter();
		std::cout << "PowerJump set\n";
		isDeleted = true;

		delete this;
	}
}

void PowerUpJump::update(Player& player, sf::RenderWindow& window)
{
	if (!isDeleted) {
		window.draw(*this);
		setAttribute(player);
	}
}

PowerUpJump::~PowerUpJump()
{
	std::cout << "Powerup usuniety\n";
}
