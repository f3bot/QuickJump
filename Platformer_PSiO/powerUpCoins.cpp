#include "powerUpCoins.h"

powerUpCoins::powerUpCoins(Player& player, sf::RenderWindow& window)
{
	if (!t.loadFromFile("assets/moneta_power.png")) {
		std::cerr << "Nie wczytano tekstury grziba\n";
	}

	setTexture(t);
	position = generatePosition(player, window);
	setScale({ 2,2 });
	setPosition(position);

	std::cout << position.x << " " << position.y << std::endl;
	isDeleted = false;
}

void powerUpCoins::setAttribute(Player& player)
{
	std::cout << "A\n";
}

void powerUpCoins::drawTo(sf::RenderWindow& window)
{
	window.draw(*this);
}
