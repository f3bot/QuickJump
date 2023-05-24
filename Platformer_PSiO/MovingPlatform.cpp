#include "MovingPlatform.h"
#include "Player.h"

void MovingPlatform::moveHorizontally(Player& player)
{
	if (movingPlatPosition.x < 0) {
		movingRect.move(0 , 2.5f);
		if (playerPlatformContact) {
			player.horizontalSpeed = 2.5f;
		}
	}
	else if (movingPlatPosition.x > 600) {
		movingRect.move(0, -2.5f);
		if (playerPlatformContact) {
			player.horizontalSpeed = -2.5f;
		}
	}
	

}

void MovingPlatform::movingPlatformCollision(Player& player)
{
		float leftPlat = getGlobalBounds().left;
		float topPlat = getGlobalBounds().top;
		float rightPlat = getGlobalBounds().left + getGlobalBounds().width;
		float bottomPlat = getGlobalBounds().top + getGlobalBounds().height;

		float leftPlayer = player.getGlobalBounds().left;
		float topPlayer = player.getGlobalBounds().top;
		float rightPlayer = player.getGlobalBounds().left + player.getGlobalBounds().width;
		float bottomPlayer = player.getGlobalBounds().top + player.getGlobalBounds().height;

		if (bottomPlayer >= topPlat && bottomPlayer <= bottomPlat && leftPlayer >= leftPlat && rightPlayer <= rightPlat) {
			if (player.getVertical() >= 0) {
				playerPlatformContact = true;
				player.isGrounded = true;
			}
		}
}

MovingPlatform::MovingPlatform(float xPos, float yPos)
{ 
	std::cout << "Debug moving Platform\n";

	playerPlatformContact = false;
	movingPlatPosition.x = xPos;
	movingPlatPosition.y = yPos;

	std::cout << movingPlatPosition.x << " " << movingPlatPosition.y << std::endl;

	movingRect.setSize({ 200,30 });
	movingRect.setFillColor(sf::Color::Red);
}

void MovingPlatform::DrawTo(sf::RenderWindow& window)
{
	window.draw(movingRect);
	std::cout << " a\n";
}
