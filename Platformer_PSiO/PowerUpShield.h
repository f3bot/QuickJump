#include <SFML/Graphics.hpp>
#include "PowerUp.h"
#include "Player.h"
#pragma once

class PowerUpShield : public PowerUp, public sf::Sprite
{
private:
	sf::Vector2f position;
	sf::Texture t;

	bool isDeleted;

public:
	PowerUpShield(Player& player, sf::RenderWindow& window);

	bool collideWithPlayer(Player& player) const override {
		if (player.getGlobalBounds().intersects(getGlobalBounds())) {
			std::cout << "Kolizja\n";
		}
		return player.getGlobalBounds().intersects(getGlobalBounds());
	}

	void setAttribute(Player& player) override;

	void drawTo(sf::RenderWindow& window);

	void update(Player& player, sf::RenderWindow& window);
};

