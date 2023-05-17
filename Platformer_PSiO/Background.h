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
	Background();
	void changeTexture(sf::Texture t);
	void drawBackground(sf::RenderWindow& window);
};

