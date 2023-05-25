#pragma once
#include <SFML/Graphics.hpp>
#include "Background.h"
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <chrono>
#include <thread>

class Player : public sf::Sprite
{

private:

	//Movement variables

	bool isJumping;
	bool isDead;

	const float gravitationalForce = 0.05f;

	//Bounds
	sf::RectangleShape bounds;

	//Texture Variables

	sf::Texture playerTexture;


	sf::Texture breathingTexture;
	std::vector<sf::IntRect> BreathingTextureVector;

	sf::Texture jumpingTexture;
	sf::Texture landingTexture;

	sf::Texture runningTexture;
	std::vector<sf::IntRect> RunningTextureVector;

	



	float animationTimeIdle;
	float animationTimeRun;
	int animationStateIdle;
	int animationStateRun;

public:
	bool left;
	bool right;

	bool canMove;

	sf::Vector2f position;
	bool isGrounded;
	//Constructors and Destructors

	double verticalSpeed;
	double horizontalSpeed;

	Player(sf::RenderWindow& window);

	//Movement

	void movementJump();
	void movementHorizontal();
	void handleEvents(sf::Event& e);

	//Drawing and Collision

	void drawTo(sf::RenderWindow& window);
	void borderCollision(sf::RenderWindow& window);

	//Textures handling **Void - displaying animation, bool - loading everything

	bool handleBreathing();
	void setBreathing(float dt);

	bool handleJumping();
	void setJumping();

	bool handleRunning();
	void setRunning(float dt);

	void handleTextureChange(float dt); //Handle all texture changes 

	//Getters and Setters

	double getVertical();
	double setVertical(double s);

	double getHorizontal();

	bool getJumping();

	//Score and Death handling
	bool getDead();
	void setDead();
};

