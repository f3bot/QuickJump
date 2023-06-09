#include "PowerUpShield.h"

PowerUpShield::PowerUpShield(Player& player, sf::RenderWindow& window)
{
	if (!t.loadFromFile("assets/shield_power.png")) {
		std::cerr << "Nie wczytano tekstury grziba\n";
	}

	setTexture(t);
	position = generatePosition(player, window);
	setScale({ 2,2 });
	setPosition(position);

	std::cout << position.x << " " << position.y << std::endl;
	isDeleted = false;
}

void PowerUpShield::setAttribute(Player& player)
{
	if (collideWithPlayer(player)) {
		player.setShielded(true);
		std::cout << "PowerJump set\n";
		isDeleted = true;
	}
}

void PowerUpShield::update(Player& player, sf::RenderWindow& window)
{
	if (!isDeleted && this != nullptr) {
		setAttribute(player);
		window.draw(*this);
	}
}
