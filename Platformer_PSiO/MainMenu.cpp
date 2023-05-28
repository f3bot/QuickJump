#include "MainMenu.h"
#include <iostream>
#include "Options.h"

MainMenu::MainMenu(float width, float height)
{
	if (!font.loadFromFile("fonts/font.ttf")) {
		std::cerr << "Nie wczytano font\n";
	}

	std::vector<std::string> strings = {
		"Play", "Options", "Credits"
	};

	std::vector<sf::Vector2f> position = {
		{200,150}, {100,300}, {100,450}
	};

	for (int i = 0; i < max_num - 1; i++) {
		mainMenu[i].setFont(font);
		mainMenu[i].setFillColor(sf::Color::White);
		mainMenu[i].setCharacterSize(80);
		mainMenu[i].setString(strings[i]);
		mainMenu[i].setPosition(position[i]);
	}

	MainMenuSelected = -1;
	gameStarted = false;

	showCredits = false;
	showOptions = false;

}
void MainMenu::moveUp()
{
	if (MainMenuSelected - 1 >= 0) {
		mainMenu[MainMenuSelected].setFillColor(sf::Color::White);

		MainMenuSelected--;

		if (MainMenuSelected == -1) {
			MainMenuSelected = 2;
		}
		mainMenu[MainMenuSelected].setFillColor(sf::Color::Red);
	}
}

void MainMenu::moveDown()
{
	if (MainMenuSelected + 1 < max_num - 1) {
		mainMenu[MainMenuSelected].setFillColor(sf::Color::White);
		MainMenuSelected++;
		if (MainMenuSelected == 4) {
			MainMenuSelected = 0;
		}
		
		mainMenu[MainMenuSelected].setFillColor(sf::Color::Red);
	}
}

bool MainMenu::getState()
{
	return gameStarted;
}

void MainMenu::processEvents(sf::Event& e)
{
	if (e.type == sf::Event::KeyPressed) {
		if (e.key.code == sf::Keyboard::Up) {
			moveUp();
			if (showOptions) {
				options.moveUp();
			}
		}

		if (e.key.code == sf::Keyboard::Down) {
			moveDown();
			if (showOptions) {
				options.moveDown();
			}
		}

		if (e.key.code == sf::Keyboard::Enter) {
			if (MainMenuSelected == 0) {
				gameStarted = true;
			}

			if (MainMenuSelected == 1) {
				showOptions = true;
			}

			if (MainMenuSelected == 2) {
				showCredits = true;
			}
		}
		if (e.key.code == sf::Keyboard::Left || e.key.code == sf::Keyboard::Right) {
			if (showOptions) {
				options.setIndex(e);
				options.moveLeftRightSprites();
			}
		}
	}
}


void MainMenu::drawTo(sf::RenderWindow& window)
{

	if (showOptions) {
		options.drawTo(window);
	}
	else if (showCredits) {

	}
	else {
		for (int i = 0; i < max_num - 1; i++) {
			window.draw(mainMenu[i]);
		}
	}

}

int MainMenu::MainMenuPressed()
{
	return MainMenuSelected;
}

MainMenu::~MainMenu()
{
}
