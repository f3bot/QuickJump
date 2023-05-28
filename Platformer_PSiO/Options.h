#pragma once
#include <SFML/Graphics.hpp>

#define max_num 3

class Options
{
private:
	sf::Text optionsText[max_num];
	sf::Text mapChoice[2];
	//Values that'll represent the index of each character
	int characterState;
	int mapSelected;

	int selectedSpriteIndex;
	int selectedMapIndex;
	sf::RectangleShape boundingBox;

	int optionsSelected;
	sf::Font font;
	sf::Font font2;

	bool displayOptions;

	sf::Sprite jungleGuy;
	sf::Sprite otherGuy;

	sf::Texture jungleGuyTexture;
	sf::Texture otherGuyTexture;


public:
	Options();

	void drawTo(sf::RenderWindow& window);

	void moveUp();
	void moveDown();

	bool handleTextures();

	int setIndex(sf::Event& e);
	void moveLeftRightSprites();

	int returnMapSelected();
	int returnselectedSpriteIndex();

	void processEvents(sf::Event& e);

};

