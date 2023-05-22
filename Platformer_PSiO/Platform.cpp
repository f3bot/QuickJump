#include "Platform.h"

Platform::Platform(std::vector<Platform>& platVec, float xPos, float yPos)
{
	rect = new sf::RectangleShape();
	size.x = 200;
	size.y = 25;
	rect->setSize(size);
	rect->setPosition(xPos, yPos);
	std::cout << "Utworzono platforme\n";
	std::cout << rect->getPosition().x << "  " << rect->getGlobalBounds().top << std::endl;
	handleTexture();

	platVec.emplace_back(*this);
}

Platform::~Platform()
{
	delete this->rect;
	std::cout << "Usunieto platforme\n";
}

void Platform::drawTo(sf::RenderWindow& window)
{
	window.draw(*rect);
}

void Platform::playerBlockCollision(Player& player)
{
	float leftPlat = this->rect->getGlobalBounds().left;
	float topPlat = this->rect->getGlobalBounds().top;
	float rightPlat = this->rect->getGlobalBounds().left + this->rect->getGlobalBounds().width;
	float bottomPlat = this->rect->getGlobalBounds().top + this->rect->getGlobalBounds().height;

	float leftPlayer = player.getGlobalBounds().left;
	float topPlayer = player.getGlobalBounds().top;
	float rightPlayer = player.getGlobalBounds().left + player.getGlobalBounds().width;
	float bottomPlayer = player.getPosition().y + player.getGlobalBounds().height;


	if (this->rect->getGlobalBounds().intersects(player.getGlobalBounds())) {
		if (player.getVertical() > 0) {
			if (bottomPlayer <= topPlat + 16 && bottomPlayer <= bottomPlat) {
				player.setPosition(player.getPosition().x, topPlat);
				player.isGrounded = true;
			}
		}
	}
	else {
		player.isGrounded = false;
	}
}

void Platform::checkForFalling(Player& player)
{
	sf::FloatRect platformBounds = this->rect->getGlobalBounds();
	sf::FloatRect playerBounds = player.getGlobalBounds();

}

bool Platform::handleTexture()
{
	if (!t.loadFromFile("assets/decorative_obj.png")) {
		std::cerr << "Nie wczytano tekstury platformy\n";
		return false;
	}
	else { 
		std::cerr << "Wczytano teksture\n";
	}
	t.setRepeated(true);
	this->rect->setTexture(&t);
	this->rect->setTextureRect(sf::IntRect(400, 144, 96 ,16));

	return true;
}

void Platform::moveUp(float verticalSpeed)
{
	this->rect->move(0, -1 * verticalSpeed);
}
