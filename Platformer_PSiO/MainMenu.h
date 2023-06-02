#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Options.h"
#include "AnimatedGIF.h"
#include "Platform.h"
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


	void processEvents(sf::Event& e, Player& player, Background& background, std::vector<Platform*> platVec); 

	int MainMenuPressed();

	~MainMenu();

	void deleteListener();

	std::string getUsername(sf::RenderWindow& window);

	std::string returnUser();

private:
	std::string username;
	sf::Text currentUser;

	AnimatedGIF* gif;

	sf::Sprite gifSprite;

	Options *options;

	int MainMenuSelected;
	sf::Font font;
	sf::Text mainMenu[3];

	sf::Text inputUsernameText;

	bool showOptions;
	bool showCredits;
	bool showMenu;

	bool userEntered;

	bool gameStarted;
};

