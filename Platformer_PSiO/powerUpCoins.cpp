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

	coins.clear();
}

void powerUpCoins::setAttribute(Player& player)
{
	std::cout << "A\n";
}

void powerUpCoins::spawnCoins(Player& player, Platform* plat)
{
	coins = {
		new Coin(player, plat),
		new Coin(player, plat),
		new Coin(player, plat),
		new Coin(player, plat),
		new Coin(player, plat),

	};
}

void powerUpCoins::drawTo(sf::RenderWindow& window)
{
	window.draw(*this);
}

void powerUpCoins::update(Player& player, sf::RenderWindow& window)
{
	if (!isDeleted) {
		window.draw(*this);
		setAttribute(player);
	}
}
