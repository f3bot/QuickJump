#pragma once
#include <SFML/Graphics.hpp>

class Player;

class playerBarrier :public sf::Sprite
{
private:
	sf::Texture t;
	sf::Vector2f position;

	sf::RectangleShape bounds;

public:
	playerBarrier(Player& player);
	void updatePosition(Player& player);
	void drawTo(Player& player, sf::RenderWindow& window);
	~playerBarrier();
};

