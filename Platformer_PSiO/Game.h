#pragma once
#include <vector>
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
public:
	void initVariables();
	void initWindowSettings();
	void movePlatforms(Player& player, std::vector<Platform> platVec);
	int run();
	Game();
};

