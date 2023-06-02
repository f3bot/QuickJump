#pragma once
#include "PowerUp.h"
#include <SFML/Graphics.hpp>

class powerUpCoins : public PowerUp, public sf::Sprite
{
private:
	sf::Vector2f position;
	sf::Texture t;

	bool isDeleted;
public:
	powerUpCoins(Player& player, sf::RenderWindow& window);

	bool collideWithPlayer(Player& player) const override {
		if (player.getGlobalBounds().intersects(getGlobalBounds())) {
			std::cout << "Kolizja\n";
		}
		return player.getGlobalBounds().intersects(getGlobalBounds());
	}

	void setAttribute(Player& player) override;

	void spawnCoins();

	void drawTo(sf::RenderWindow& window);

	void update(Player& player, sf::RenderWindow& window);
};

