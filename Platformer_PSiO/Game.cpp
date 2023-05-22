#include "Game.h"
#include "Background.h"
#include "Player.h"
#include "Platform.h"
#include <iostream>
void Game::initVariables()
{

}


void Game::movePlatforms(Player& player, std::vector<Platform> platVec)
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

    std::vector<Platform> platformVec;

    Background background_texture;
    Player player;
    Platform plat2( 200.f, 600.f);

    platformVec.emplace_back(plat2);
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
        }

        window.clear();
        background_texture.drawBackground(window);
        player.drawTo(window);
        for (int i = 0; i < platformVec.size(); ++i) {
            platformVec[i].drawTo(window);
            platformVec[i].playerBlockCollision(player);
        }
        if (player.getJumping()) {
            movePlatforms(player, platformVec);
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
