#include "Options.h"
#include <iostream>

Options::Options()
{

	handleTextures();

	otherGuy.setPosition(150, 300);
	jungleGuy.setPosition(400 ,300);

	if (!font.loadFromFile("fonts/font.ttf")) {
		std::cerr << "Nie wczytano font\n";
	}

	if (!font2.loadFromFile("fonts/font2.ttf")) {
		std::cerr << "Nie wczytano fonta 2\n";
	}

	std::vector<std::string> strings = {
		"Select", "Character", "Select Map"
	};

	std::vector<sf::Vector2f> position = {
		{165,50}, {90, 150},  {90,500}
	};

	for (int i = 0; i < max_num ; i++) {
		optionsText[i].setFont(font);
		optionsText[i].setFillColor(sf::Color::White);
		optionsText[i].setCharacterSize(64);
		optionsText[i].setString(strings[i]);
		optionsText[i].setPosition(position[i]);
	}

	std::vector<std::string> mapNames = {
		"Dark Church", "Gloomy Caves"
	};

	std::vector<sf::Vector2f> mapPosition = {
		{120, 650}, {120 ,720}
	};

	for (int i = 0; i < 2; i++) {
		mapChoice[i].setFont(font2);
		mapChoice[i].setFillColor(sf::Color::White);
		mapChoice[i].setCharacterSize(40);
		mapChoice[i].setString(mapNames[i]);
		mapChoice[i].setPosition(mapPosition[i]);

	}
	
	characterState = 0;
	mapSelected = 1;
	optionsSelected = 0;
	displayOptions = false;

	selectedSpriteIndex = 1;

	boundingBox.setPosition(jungleGuy.getPosition());
	boundingBox.setSize(sf::Vector2f(jungleGuy.getGlobalBounds().width, jungleGuy.getGlobalBounds().height));
	boundingBox.setFillColor(sf::Color::Transparent);
	boundingBox.setOutlineColor(sf::Color::Red);
	boundingBox.setOutlineThickness(2.0f);

}

bool Options::handleTextures()
{
	if (!jungleGuyTexture.loadFromFile("assets/Jungle Asset Pack/Character/sprites/jump.png")) {
		std::cerr << "Could not load texture in options class\n";
	}

	if (!otherGuyTexture.loadFromFile("assets/Medieval Warrior Pack 2/Sprites/Idle.png")) {
		std::cerr << "Could not load texture in options class\n";
	}

	jungleGuy.setTexture(jungleGuyTexture);
	otherGuy.setTexture(otherGuyTexture);
	otherGuy.setTextureRect(sf::IntRect({62,54,25,41}));
	
	otherGuy.setScale({ 3,3 });
	jungleGuy.setScale({ 3.5,3.5 });

	return false;
}

int Options::setIndex(sf::Event& e)
{
	if (e.key.code == sf::Keyboard::Left) {
		selectedSpriteIndex = 1;
		boundingBox.setSize({otherGuy.getGlobalBounds().width, otherGuy.getGlobalBounds().height});
		std::cout << selectedSpriteIndex << std::endl;
	}
	else if (e.key.code == sf::Keyboard::Right) {
		selectedSpriteIndex = 0;
		boundingBox.setSize({ jungleGuy.getGlobalBounds().width, jungleGuy.getGlobalBounds().height });
		std::cout << selectedSpriteIndex << std::endl;
	}

	return selectedSpriteIndex;
}

void Options::moveLeftRightSprites()
{

	if (selectedSpriteIndex == 0) {
		boundingBox.setPosition(jungleGuy.getPosition());
	}
	else if (selectedSpriteIndex == 1) {
		boundingBox.setPosition(otherGuy.getPosition());
	}
}

int Options::returnMapSelected()
{
	return mapSelected;
}

int Options::returnselectedSpriteIndex()
{
	return selectedSpriteIndex;
}

void Options::drawTo(sf::RenderWindow& window)
{
	for (int i = 0; i < max_num; i++) {
		window.draw(optionsText[i]);
	}

	for (int i = 0; i < 2; i++) {
		window.draw(mapChoice[i]);
	}
	window.draw(jungleGuy);
	window.draw(otherGuy);


	window.draw(boundingBox);
}
void Options::moveUp()
{
	if (mapSelected > 0) {
		mapChoice[mapSelected].setFillColor(sf::Color::White); 
		mapSelected--;
		mapChoice[mapSelected].setFillColor(sf::Color::Yellow);
	}
}

void Options::moveDown()
{
	if (mapSelected < 1) {
		mapChoice[mapSelected].setFillColor(sf::Color::White);
		mapSelected++;
		mapChoice[mapSelected].setFillColor(sf::Color::Yellow);
	}
}