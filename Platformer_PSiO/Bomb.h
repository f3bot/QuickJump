#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include <random>
#include <ctime>

class Bomb : public sf::Sprite
{
private:
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Texture bombTexture;
	sf::Texture explosionTexture;

	float animationTimeExplosion;
	int animationStateExplosion;

	bool canMove;
	
	bool hasSetTextureRect;

	std::vector<sf::IntRect> explosionVector;

	const float gravitationalForce = 3.f;
public:
	Bomb();
	~Bomb();
	void collisionWithPlayer(Player& player, float dt);
	void resetPosition(sf::RenderWindow& window, Player& player);
	void fallDown();
	void moveUp(float speed);
	float randomFloat(float min, float max);
	bool initializeVector();
	void animateExplosion(float dt, Player& player);
	void update(Player& player, sf::RenderWindow& window, float dt);
};

