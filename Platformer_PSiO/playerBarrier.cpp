#include "playerBarrier.h"
#include "Player.h"

playerBarrier::playerBarrier(Player& player)
{
	if (!t.loadFromFile("assets/barrierSprite.png")) {
		std::cerr << "Nie wczytano tekstury bariery\n";
	}

	std::cout << "Tworze bariere\n";

	setTexture(t);
	setPosition(player.getGlobalBounds().top, player.getGlobalBounds().left);
	setScale({ 0.25,0.25 });

	bounds.setSize(sf::Vector2f(getGlobalBounds().width, getGlobalBounds().height));
	bounds.setOutlineThickness(2.f);
	bounds.setOutlineColor(sf::Color::Red);
	bounds.setFillColor(sf::Color::Transparent);
}

void playerBarrier::updatePosition(Player& player)
{
	bounds.setPosition(getPosition());
	setPosition(player.getPosition());
}

void playerBarrier::drawTo(Player& player, sf::RenderWindow& window)
{
	updatePosition(player);
	window.draw(bounds);
	window.draw(*this);
}

playerBarrier::~playerBarrier()
{
	std::cout << "Usuwam bariere\n";
}
