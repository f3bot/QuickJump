#pragma once
#include <SFML/Graphics.hpp>
#include "playerBarrier.h"
#include "Background.h"
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <chrono>
#include <thread>

class Player : public sf::Sprite
{

private:
	//Texture selection
	int selectedTexture;

	//Movement variables

	bool isJumping;
	bool isDead;

	const float gravitationalForce = 0.09f;

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


	playerBarrier* barrier;



	float animationTimeIdle;
	float animationTimeRun;
	int animationStateIdle;
	int animationStateRun;

	//PowerUp dependant bools
	bool isShielded;
	bool isPowerJumped;

	bool barrierCreated;

	int jumpingCounter;
	//Coin powerUp will be linked with coin

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

	void movementJump(Background& background);
	void movementHorizontal(Background& background);
	void handleEvents(sf::Event& e);

	//Drawing and Collision

	void drawTo(sf::RenderWindow& window, Background& background);
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

	int setSelectedTexture(int s);

	void setTextures();

	bool getJumping();

	//Getters for powerup classes

	bool getPowerJump();
	bool getShielded();

	void setPowerJumped(bool s);
	void setShielded(bool s);

	void setCounter();

	//Score and Death handling
	bool getDead();
	void setDead();
	
	void updateAll(float dt, sf::RenderWindow& window, sf::Event& e, Background& background);

	void updateShield(sf::RenderWindow& window);
};

