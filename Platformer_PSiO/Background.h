#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Background :public sf::Sprite
{
private:
	sf::Texture texture;
	sf::Texture lowerTexture_set;
	sf::Sprite lowerTexture;
public:
	Background(sf::RenderWindow& window);
	void changeTexture(sf::Texture t);
	void updatePosition(sf::RenderWindow& window, sf::View& view);
	void drawBackground(sf::RenderWindow& window);
};

