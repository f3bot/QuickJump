#pragma once
#include <vector>
#include <iostream>
#include <random>
#include <ctime>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Background.h"
#include "Platform.h"
#include "Player.h"
#include "MainMenu.h"
#include "PowerUpShield.h"
#include "PowerUpJump.h"
#include "powerUpCoins.h"
#include "Coin.h"
class Game

{
private:
	sf::RenderWindow window;
	const unsigned int width = 600;
	const unsigned int height = 800;
	std::vector<Platform*> platformVec;
	PowerUpShield* p1;
	PowerUpJump* p2;

	bool objectCreated;

public:
	void initVariables();
	void initWindowSettings();
	void movePlatforms(Player& player);
	void handleWorldGeneration(Player& player);
	sf::Vector2f randomCoordinates();
	bool deleteOutOfBoundsPlatforms(Player& player);
	void initializeGameWithPlatforms();
	int run();

	void updateMainGame(Player& player);

	float randomFloat(float min, float max);
	Game();

	void saveToCsv(std::string filename, Coin* coin, MainMenu* menu, Player& player);

	bool playerPowerCollision(Player& player, PowerUpShield* shield, PowerUpJump* jump);

	void determineDelete(Player& player);


	void updatePowers(Player& player, sf::RenderWindow& window);
};

