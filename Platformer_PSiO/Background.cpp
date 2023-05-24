#include "Background.h"

Background::Background(sf::RenderWindow& window) : sf::Sprite()
{
	if (!texture.loadFromFile("assets/background_0_x.png")) {
		std::cerr << "Nie wczytano tekstury background\n";
	}

	if (!lowerTexture_set.loadFromFile("assets/Background_1.png")) {
		std::cerr << "Nie wczytano dolnej background\n";
	}
	setTexture(texture);
	setScale({ 1.7f, 1.7f });
	setPosition(-300.f, -200.f);
}

void Background::drawBackground(sf::RenderWindow& window)
{
	window.draw(*this);
}
