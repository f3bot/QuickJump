#include "Background.h"

Background::Background(sf::RenderWindow& window) : sf::Sprite()
{
	if (!texture.loadFromFile("assets/background_0.png")) {
		std::cerr << "Nie wczytano tekstury background\n";
	}

	if (!lowerTexture_set.loadFromFile("assets/Background_1.png")) {
		std::cerr << "Nie wczytano dolnej background\n";
	}
	setTextureRect({ 0,0,600,800 });
	setTexture(texture);
	lowerTexture.setTexture(lowerTexture_set);
	lowerTexture.setPosition({0,200});
	lowerTexture.setScale(2,2);

	setScale(sf::Vector2f(window.getSize().x / getGlobalBounds().width, window.getSize().y / getGlobalBounds().height));
}

void Background::updatePosition(sf::RenderWindow& window, sf::View& view)
{
	setPosition(view.getCenter().x - window.getSize().x / 2, view.getCenter().y - window.getSize().y / 2);
}

void Background::drawBackground(sf::RenderWindow& window)
{

	window.draw(*this);
	window.draw(lowerTexture);
}
