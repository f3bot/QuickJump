#include "Spikes.h"
#include <SFML/Graphics.hpp>

Spikes::Spikes() : sf::RectangleShape()
{
	if (!texture.loadFromFile("assets/spikes.png")) {
		std::cerr << "Nie wczytano tekstury kolców\n";
	}
	texture.setRepeated(true);


	setSize(sf::Vector2f(1200,100));
	//setTexture(&texture);

}

void Spikes::updatePosition(sf::RenderWindow& window, Player& player)
{
	if (player.getVertical() < 0) {
		setPosition(0, player.getPosition().y + 600);
	}
}

void Spikes::update(sf::RenderWindow& window, Player& player)
{
	updatePosition(window, player);
	window.draw(*this);
}
