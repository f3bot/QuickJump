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
	setScale({ 0.15,0.15 });

	bounds.setSize(sf::Vector2f(getGlobalBounds().width, getGlobalBounds().height));
	bounds.setOutlineThickness(2.f);
	bounds.setOutlineColor(sf::Color::Red);
	bounds.setFillColor(sf::Color::Transparent);
}

void playerBarrier::updatePosition(Player& player)
{
	setPosition(player.getPosition().x - 20, player.getPosition().y - 20);
}

void playerBarrier::drawTo(Player& player, sf::RenderWindow& window)
{
	updatePosition(player);
	window.draw(*this);
}

playerBarrier::~playerBarrier()
{
	std::cout << "Usuwam bariere\n";
}
