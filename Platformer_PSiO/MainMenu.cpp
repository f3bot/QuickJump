#include "MainMenu.h"
#include "Player.h"
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

	currentUser.setFont(font);
	currentUser.setPosition(150.f, 225.f);
	inputUsernameText.setFont(font);

	MainMenuSelected = 0;
	gameStarted = false;

	showCredits = false;
	showOptions = false;


	options = new Options();
	gif = new AnimatedGIF("assets/gggif.gif");

	userEntered = false;

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

void MainMenu::processEvents(sf::Event& e, Player& player, Background& background, std::vector<Platform*> platVec)
{
	if (e.type == sf::Event::KeyPressed) {
		if (e.key.code == sf::Keyboard::Up) {
			if (showOptions) {
				options->moveUp();
			}
			else {
				moveUp();
			}
		}

		if (e.key.code == sf::Keyboard::Down) {
			if (showOptions) {
				options->moveDown();
			}
			else {
				moveDown();
			}
		}

		if (e.key.code == sf::Keyboard::Enter) {
			if (MainMenuSelected == 0) {
				background.setSelected(options->returnMapSelected());
				background.setTexture_();
				player.setSelectedTexture(options->returnselectedSpriteIndex());
				player.setTextures();
				for (auto a : platVec) {
					a->setSelected(options->returnMapSelected());
					a->setTextures();
				}
				if (!showOptions) {
					gameStarted = true;
				}
			}

			if (MainMenuSelected == 1) {
				showOptions = true;
			}

			if (MainMenuSelected == 2) {
				showCredits = true;
			}
		}

		if (e.key.code == sf::Keyboard::Escape) {
			showOptions = false;
			player.setSelectedTexture(options->returnselectedSpriteIndex());
		}

		if (e.key.code == sf::Keyboard::Left || e.key.code == sf::Keyboard::Right) {
			if (showOptions) {
				options->setIndex(e);
				options->moveLeftRightSprites();
			}
		}
	}
}

void MainMenu::drawTo(sf::RenderWindow& window)
{
	gif->update(gifSprite);
	window.draw(gifSprite);

	if (showOptions) {
		options->drawTo(window);
	}
	else if (showCredits) {
		// Draw credits here
	}
	else {
		// Draw main menu
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
	std::cout << "Menu zniszczone\n";
}

void MainMenu::deleteListener()
{
	if (gameStarted) {
		delete this;
	}
}

std::string MainMenu::getUsername(sf::RenderWindow& window)
{
	inputUsernameText.setString("Wpisz username");
	inputUsernameText.setPosition(150, 100);
	sf::Event event;
	while (!userEntered)
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode == '\r')
				{
					userEntered = true;
				}
				else if (event.text.unicode == '\b')
				{
					username.pop_back();
				}
				else if (event.text.unicode < 128)
				{
					username += static_cast<char>(event.text.unicode);
				}
			}
		}

		currentUser.setString(username);

		window.clear();
		window.draw(inputUsernameText);
		window.draw(currentUser);
		window.display();
	}
	return username;
}

std::string MainMenu::returnUser()
{
	return username;
}
