#include <SFML/Graphics.hpp>
#include "Options.h"
#pragma once

#define max_num 4

class MainMenu
{

public:
	MainMenu(float width, float height);

	void drawTo(sf::RenderWindow& window);
	void moveUp();
	void moveDown();

	bool getState();

	void processEvents(sf::Event& e);

	int MainMenuPressed();

	~MainMenu();



private:

	Options options;

	int MainMenuSelected;
	sf::Font font;
	sf::Text mainMenu[3];

	bool showOptions;
	bool showCredits;

	bool gameStarted;
};

