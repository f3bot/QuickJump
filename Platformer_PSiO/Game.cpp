#include "Game.h"
#include "Background.h"
#include "Player.h"
#include "Platform.h"
#include <iostream>
void Game::initVariables()
{

}


void Game::movePlatforms(Player& player)
{
    for (int i = 0; i < platVec.size(); i++) {
        std::cout << "Before move: " << platVec[i].getPosition().x << "  " << platVec[i].getPosition().y << std::endl;
        platVec[i].moveUp(player.getVertical());
        std::cout << "After move: " << platVec[i].getPosition().x << "  " << platVec[i].getPosition().y << std::endl;
    }
}

int Game::run()
{
    sf::Clock clock;

    Background background_texture;
    Player player;
    Platform plat(platVec,200.f,700.f);
    Platform plat2(platVec, 200.f, 600.f);
    Platform plat3(platVec, 200.f ,500.f);

    sf::RenderWindow window(sf::VideoMode(width, height), "Platformer!");

    window.setFramerateLimit(144);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            player.handleEvents(event);
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::C) {
                    for (int i = 0; i < platVec.size(); i++) {
                        std::cout << platVec[i].getPosition().x << "  " << platVec[i].getPosition().y << std::endl;
                    }
                }
            }
        }

        window.clear();
        background_texture.drawBackground(window);
        player.drawTo(window);
        for (int i = 0; i < platVec.size(); ++i) {
            platVec[i].drawTo(window);
            platVec[i].playerBlockCollision(player);
            if (player.getJumping()) {
                movePlatforms(player);
            }
        }
        player.movementJump();
        clock.restart();
        player.movementHorizontal(clock.getElapsedTime().asMicroseconds());
        player.handleTextureChange(clock.getElapsedTime().asMicroseconds());
        player.borderCollision(window);
        window.display();
    }

    return 0;
}

Game::Game()
{
	window.setSize(sf::Vector2u(width, height));
	window.setTitle("Platformer");
}
