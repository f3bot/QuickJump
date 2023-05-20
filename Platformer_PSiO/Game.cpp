#include "Game.h"
#include "Background.h"
#include "Player.h"
#include "Platform.h"
#include <iostream>
void Game::initVariables()
{

}


int Game::run()
{
    sf::Clock clock;

    Background background_texture;
    Player player;
    Platform plat;


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
        plat.drawTo(window);
        player.movementJump();
        player.movementHorizontal(clock.getElapsedTime().asMicroseconds());
        player.handleTextureChange(clock.getElapsedTime().asMicroseconds());
        plat.playerBlockCollision(player);
        player.borderCollision(window);
        clock.restart();
        window.display();
    }

    return 0;
}

Game::Game()
{
	window.setSize(sf::Vector2u(width, height));
	window.setTitle("Platformer");
}
