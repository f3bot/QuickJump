#pragma once
#include <vector>
#include <iostream>
#include <random>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "Background.h"
#include "Platform.h"
#include "Player.h"
class Game

{
private:
	sf::RenderWindow window;
	const unsigned int width = 600;
	const unsigned int height = 800;
	std::vector<Platform*> platformVec;
public:
	void initVariables();
	void initWindowSettings();
	void movePlatforms(Player& player);
	void handleWorldGeneration(Player& player);
	sf::Vector2f randomCoordinates();
	bool deleteOutOfBoundsPlatforms(Player& player);
	void initializeGameWithPlatforms();
	int run();

	float randomFloat(float min, float max);
	Game();
};

