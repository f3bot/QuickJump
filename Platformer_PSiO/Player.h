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

	//Movement variables


	bool isJumping;
	bool isDead;
	bool left;
	bool right;
	const float gravitationalForce = 0.1f;
	double verticalSpeed;
	double horizontalSpeed;

	//Bounds

	sf::Vector2f position;
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
	bool isGrounded;
	//Constructors and Destructors

	Player();

	//Movement

	void movementJump();
	void movementHorizontal(float dt);
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


	//Score and Death handling
};

