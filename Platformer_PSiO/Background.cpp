#include "Background.h"

Background::Background(sf::RenderWindow& window) : sf::Sprite()
{
	if (!texture.loadFromFile("assets/background_0_x.png")) {
		std::cerr << "Nie wczytano tekstury background\n";
	}
	selectedMap = 0;
	setTexture(texture);
	setScale({ 1.7f, 1.7f });
	setPosition(-300.f, -200.f);
}

void Background::setTexture_()
{
	if (selectedMap == 0) {
		if (!texture.loadFromFile("assets/background_0_x.png")) {
			std::cerr << "Nie wczytano tekstury background\n";
		}
	}
	else {
		if (!texture.loadFromFile("assets/Background_caves.png")) {
			std::cerr << "Nie wczytano tekstury background\n";
		}
	}
}

int Background::setSelected(int s)
{
	selectedMap = s;
	return selectedMap;
}

void Background::drawBackground(sf::RenderWindow& window)
{
	window.draw(*this);
}
