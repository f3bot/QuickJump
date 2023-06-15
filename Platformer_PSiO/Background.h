#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Background :public sf::Sprite
{
private:
	int selectedMap;

	sf::Texture texture;
	sf::Texture lowerTexture_set;
public:
	Background(sf::RenderWindow& window);
	void setTexture_();

	int setSelected(int s);
	void drawBackground(sf::RenderWindow& window);
};

