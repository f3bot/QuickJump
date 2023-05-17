#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <chrono>
#include <thread>
class Player : public sf::Sprite
{

private:
	bool isGrounded;
	bool isJumping;
	bool isDead;
	const float gravitationalForce = 0.4f;
	sf::Texture playerTexture;
	double verticalSpeed;
	double horizontalSpeed;
	sf::Vector2f position;
	bool left;
	bool right;

public:
	Player();
	void movementJump();
	void movementHorizontal();
	void handleEvents(sf::Event& e);
	void drawTo(sf::RenderWindow& window);
	void borderCollision(sf::RenderWindow& window);
};

