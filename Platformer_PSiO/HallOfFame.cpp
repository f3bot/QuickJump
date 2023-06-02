#include "HallOfFame.h"
#include "Player.h"
#include <fstream>

void HallOfFame::endEvent(sf::Event& e, sf::RenderWindow& window)
{
    if (loaded) {
            if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::Enter) {
                    window.close();
                }
            }
        }
}

HallOfFame::HallOfFame()
{
	if (!font.loadFromFile("fonts/font2.ttf")) {
		std::cout << "Font not loaded hof\n";
	}
	
	for (int i = 0; i < 5; i++) {
		winnersText[i].setFont(font);
		winnersText[i].setCharacterSize(60);
		winnersText[i].setFillColor(sf::Color::Red);
        scoreText[i].setFont(font);
        scoreText[i].setCharacterSize(60);
        scoreText[i].setFillColor(sf::Color::Red);
	}

    endGameText.setFont(font);
    endGameText.setCharacterSize(45);
    endGameText.setFillColor(sf::Color::Blue);
    endGameText.setString("Press enter to exit the game");

    found = false;
	loaded = false;

    posY = -300.f;
}

void HallOfFame::loadFromCsv(std::string filename)
{
    if (!loaded) {
        std::ifstream file;
        file.open(filename);
        if (file.is_open()) {
            std::string line;
            int i = 0;
            while (std::getline(file, line)) {
                if (i % 2 == 0) {
                    Data.push_back({line , 0});
                }
                else {
                    Data.back().score = std::stoi(line);
                }
                i++;
            }
            file.close();
            std::cout << "Loaded\n";
            loaded = true;
            

            std::sort(Data.begin(), Data.end(), compareByScore);


            for (int i = 0; i < 5; i++) {
                winnersText[i].setString(Data[i].nickname);
                scoreText[i].setString(std::to_string(Data[i].score));
            }
        }
    }
}


void HallOfFame::calculateAndSetPosition(Player& player)
{

    if (!found) {
        sf::Vector2f playerPos = player.getPosition();


        for (int i = 0; i < 5; i++) {
            winnersText[i].setPosition(playerPos.x - 200.f, playerPos.y + posY );
            scoreText[i].setPosition(playerPos.x + 200.f, playerPos.y + posY);
            posY += 100.f;
        }

        endGameText.setPosition(playerPos.x - 400.f,  playerPos.y + 400.f);

        found = true;
    }
}



void HallOfFame::drawTo(sf::RenderWindow& window)
{
    for (int i = 0; i < 5; i++) {
        window.draw(winnersText[i]);
        window.draw(scoreText[i]);
    }
    window.draw(endGameText);
}
