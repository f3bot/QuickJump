#include "Game.h"
#include "Background.h"
#include "Player.h"
#include "Platform.h"
#include "Bomb.h"
#include "Coin.h"
#include "MainMenu.h"
#include "AnimatedGIF.h"
#include "PowerUpJump.h"
#include "PowerUpShield.h"
#include "HallOfFame.h"
#include <iostream>

void Game::initVariables()
{
}

void Game::movePlatforms(Player& player)
{
    for (auto& platform : platformVec) {
        platform->moveUp(0.2 * player.getVertical());
    }
}

void Game::handleWorldGeneration(Player& player)
{
    if (deleteOutOfBoundsPlatforms(player)) {
        platformVec.push_back(new Platform(randomCoordinates().x, randomCoordinates().y));
    }
}

sf::Vector2f Game::randomCoordinates()
{
    sf::Vector2f position;
    int index = platformVec.size() - 1;

    position.x = randomFloat(50, 550);
    position.y = platformVec[index]->getPositionY() - randomFloat(200, 390);

    return position;
}

bool Game::deleteOutOfBoundsPlatforms(Player& player)
{
    bool platformsDeleted = false;

    for (auto it = platformVec.begin(); it != platformVec.end();) {
        if ((*it)->getPositionY() > player.getPosition().y + height - 100 || (*it)->getAnimationState() == 8) {
            delete* it;
            it = platformVec.erase(it);
            platformsDeleted = true;
        }
        else {
            ++it;
        }
    }

    return platformsDeleted;
}

void Game::initializeGameWithPlatforms()
{
    platformVec = {
        new Platform(200.f, 350.f),
        new Platform(200.f, 150.f),
        new Platform(200.f, -50.f),
        new Platform(200.f, -250.f),
        new Platform(200.f, -450.f),
        new Platform(200.f, -650.f),
        new Platform(200.f, -850.f)
    };
}

int Game::run()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    sf::Clock clock;
    sf::View view = window.getDefaultView();
    Bomb bomb;

    AnimatedGIF gif();
    sf::Sprite gifSprite;

    Background background_texture(window);
    Player player(window);

    initializeGameWithPlatforms();

    sf::RenderWindow window(sf::VideoMode(width, height), "Platformer!");

    window.setFramerateLimit(144);

    Coin* coin = new Coin(player, platformVec[2]);

    MainMenu* mainMenu;
    mainMenu = new MainMenu(width, height);

    HallOfFame h;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            player.handleEvents(event);
            mainMenu->processEvents(event, player, background_texture, platformVec);
            
            h.endEvent(event, window);
        }

        window.clear(sf::Color::Black);

        mainMenu->getUsername(window);

        if (!mainMenu->getState()) {
            mainMenu->drawTo(window);
            mainMenu->deleteListener();
            window.draw(gifSprite);
        }
        else {
            if (!player.getDead()) {
                background_texture.drawBackground(window);

                for (auto& platform : platformVec) {
                    platform->updateAll(player, clock.getElapsedTime().asMicroseconds(), window);
                }

                if (coin->getScore() % 10 == 0 && !objectCreated) {
                    if (randomInt(1, 2) == 1) {
                        p1 = new PowerUpShield(player, window);
                    }
                    else {
                        p2 = new PowerUpJump(player, window);
                    }
                    objectCreated = true;
                }

                update(player, window);
                updatePowers(player, window);
                player.updateAll(clock.getElapsedTime().asMicroseconds(), window, event, background_texture, view);
                bomb.update(player, window, clock.getElapsedTime().asMicroseconds());
                coin->updateCoin(player, window, clock.getElapsedTime().asMicroseconds(), platformVec[2], platformVec);
                clock.restart();
            }
            else {
                saveToCsv("output.txt", coin, mainMenu, player);
                h.updateAll(window, "output.txt", player);
            }
        }

        window.display();
    }

    return 0;
}

float Game::randomFloat(float min, float max)
{
    static std::default_random_engine e{ static_cast<long unsigned int>(time(0)) };
    std::uniform_real_distribution<float> d{ min, max };
    return d(e);
}

Game::Game()
{
    window.setSize(sf::Vector2u(width, height));
    window.setTitle("Platformer");

    p1 = nullptr;
    p2 = nullptr;
    objectCreated = false;
    dataLoaded = false;
}

void Game::saveToCsv(std::string filename, Coin* coin, MainMenu* menu, Player& player)
{
    if (player.getDead() && !dataLoaded) {
        std::fstream file;
        file.open(filename, std::ios::app);
        file << menu->returnUser() << "\n";
        file << coin->getScore();
        file << "\n";
        file.close();

        dataLoaded = true;
    }
}

bool Game::playerPowerCollision(Player& player, PowerUpShield* shield, PowerUpJump* jump)
{
    if (p1 != nullptr && player.getGlobalBounds().intersects(p1->getGlobalBounds())) {
        player.setShielded(true);
        std::cout << player.getShielded() << std::endl;
        delete p1;
        p1 = nullptr;
        objectCreated = false;
    }

    if (p2 != nullptr && player.getGlobalBounds().intersects(p2->getGlobalBounds())) {
        std::cout << "Chuj\n";
        player.setPowerJumped(true);
        player.setCounter();
        std::cout << player.getPowerJump() << std::endl;
        delete p2;
        p2 = nullptr;
        objectCreated = false;
    }

    return false;
}

void Game::updatePowers(Player& player, sf::RenderWindow& window)
{
    if (p1 != nullptr) {
        p1->update(player, window);
    }

    if (p2 != nullptr) {
        p2->update(player, window);
    }
}

void Game::update(Player& player, sf::RenderWindow& w)
{
    handleWorldGeneration(player);
    playerPowerCollision(player, p1, p2);
    //updatePowers(player, window);
}

int Game::randomInt(int min, int max){
    static std::default_random_engine e{ static_cast<long unsigned int>(time(0)) };
    std::uniform_int_distribution<int> d{ min, max };
    return d(e);
}
