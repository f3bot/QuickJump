#include "Player.h"

Player::Player() : sf::Sprite()
{
	std::cout << "Obiekt klasy gracz\n";
	if (!playerTexture.loadFromFile("assets/Jungle Asset Pack/Character/sprites/idle.gif")) {
		std::cerr << "Nie wczytano tekstury gracza\n";
	}
	setTexture(playerTexture);
	setPosition(400, 400);
	setScale({ 2,2 });
	isGrounded = false;
	verticalSpeed = 5.f;
	horizontalSpeed = 0;
	isJumping = false;
	isDead = false;
	left = false;
	right = false;
}

void Player::movementJump()
{
	if (isGrounded) {
		verticalSpeed = 0;
		isJumping = false;
	}
	else {
		verticalSpeed += gravitationalForce;
		position.y += verticalSpeed;

		move(0, verticalSpeed);
	}
	
}

void Player::movementHorizontal()
{
	if (left) {
		move(-3.5f, 0);
	}
	if (right) {
		move(3.5f, 0);
	}

}



void Player::handleEvents(sf::Event& e)
{
	if (e.type == sf::Event::KeyPressed) {
		if (e.key.code == sf::Keyboard::Z) {
			if (!isGrounded) {
				isGrounded = true;
			}
			else isGrounded = false;
		}
		if (e.key.code == sf::Keyboard::Up && !isJumping) {
			verticalSpeed = -15.f;
			isJumping = true;
			isGrounded = false;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		left = true;
		right = false;
		setScale({ -2, 2 });
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		left = false;
		right = true;
		setScale({ 2, 2 });
	}
	else {
		left = false;
		right = false;
	}
}

void Player::drawTo(sf::RenderWindow& window)
{
	setPosition(getPosition().x, position.y);
	borderCollision(window);
	window.draw(*this);
}

void Player::borderCollision(sf::RenderWindow& window)
{
	if (getGlobalBounds().top + getGlobalBounds().height > window.getSize().y) {
		isGrounded = true;
		isJumping = false;
	}
}
