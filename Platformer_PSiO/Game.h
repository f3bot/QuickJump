#pragma once
#include <SFML/Graphics.hpp>
#include "Background.h"
#include "Platform.h"
#include "Player.h"
class Game

{
private:
	sf::RenderWindow window;
	unsigned int width = 600;
	unsigned int height = 800;

public:
	void initVariables();
	void initWindowSettings();
	int run();
	Game();
};

