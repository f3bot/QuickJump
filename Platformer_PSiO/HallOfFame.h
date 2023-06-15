#include <iostream>
#pragma once
#include "Player.h"
#include <string>
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>

class HallOfFame
{
private:
	struct data {
		std::string nickname;
		int score;
	};

	std::vector<data> Data;
	
	static bool compareByScore(const HallOfFame::data& a, const HallOfFame::data& b) {
		return a.score > b.score;
	}

	sf::Text winnersText[5];
	sf::Text scoreText[5];
	sf::Font font;

	sf::Text endGameText;



	bool found;

	bool loaded;


	float posY;
public:
	HallOfFame();

	void loadFromCsv(std::string filename);

	void calculateAndSetPosition(Player& player);

	void drawTo(sf::RenderWindow& window);

	void endEvent(sf::Event& e, sf::RenderWindow& window);

	void updateAll(sf::RenderWindow& window, std::string filename, Player& player);
};

