#include "Platform.h"

Platform::Platform(float xPos, float yPos)
{
	size.x = 350;
	size.y = 35;
	rect.setSize(size);
	rect.setPosition(xPos, yPos);

	t.loadFromFile("assets/decorative_obj.png");

	handleTexture();


	std::cout << "Utworzono platforme\n";
	std::cout << rect.getPosition().x << "  " << rect.getGlobalBounds().top << std::endl;

}

Platform::~Platform()
{
	std::cout << "Usunieto platforme\n";
}

void Platform::drawTo(sf::RenderWindow& window)
{
	window.draw(rect);
}

void Platform::playerBlockCollision(Player& player)
{
	float leftPlat =  rect.getGlobalBounds().left;
	float topPlat =  rect.getGlobalBounds().top;
	float rightPlat =  rect.getGlobalBounds().left +  rect.getGlobalBounds().width;
	float bottomPlat =  rect.getGlobalBounds().top +  rect.getGlobalBounds().height;

	float leftPlayer = player.getGlobalBounds().left;
	float topPlayer = player.getGlobalBounds().top;
	float rightPlayer = player.getGlobalBounds().left + player.getGlobalBounds().width;
	float bottomPlayer = player.getGlobalBounds().top + player.getGlobalBounds().height;

	if (bottomPlayer >= topPlat && bottomPlayer <= bottomPlat && leftPlayer >= leftPlat && rightPlayer <= rightPlat) {
		if (player.getVertical() >= 0) {
				player.isGrounded = true;
		}
	}

}

void Platform::checkForFalling(Player& player)
{
	sf::FloatRect platformBounds =  rect.getGlobalBounds();
	sf::FloatRect playerBounds = player.getGlobalBounds();

}

Platform::Platform()
{
	std::cout << "Defualt Constructor\n";
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
	rect.setTexture(&t);
	rect.setTextureRect(sf::IntRect(400, 144, 96 ,16));

	return true;
}

float Platform::getPositionY()
{

	return rect.getPosition().y;
}

void Platform::moveUp(float verticalSpeed)
{
	 rect.move(0, -1 * verticalSpeed);
}
