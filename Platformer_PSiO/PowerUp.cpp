#include "PowerUp.h"

sf::Vector2f PowerUp::generatePosition(Player& player, sf::RenderWindow& window)
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	sf::Vector2f pos;
	pos.x = rand() % window.getSize().x;
	pos.y = rand() % window.getSize().y - player.getPosition().y;
	return pos;
}

bool PowerUp::checkScore(Coin& coin)
{
	return coin.getScore() % 10 == 0;
}

