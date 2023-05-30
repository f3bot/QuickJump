#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class Spikes : public sf::RectangleShape
{
private:
	sf::Texture texture;

public:
	Spikes();

	void drawTo(sf::RenderWindow& window);

	void collision(Player& player);

	void updatePosition(sf::RenderWindow& window, Player& player);

	void update(sf::RenderWindow& window, Player& player);

};

