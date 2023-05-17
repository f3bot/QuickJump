#include "Game.h"
#include "Background.h"
#include <iostream>
#include "Player.h"
void Game::initVariables()
{

}


int Game::run()
{
    sf::Clock clock;

    Background background_texture;
    Player player;

    sf::RenderWindow window(sf::VideoMode(width, height), "Platformer!");

    window.setFramerateLimit(60);

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
        player.movementJump();
        player.movementHorizontal();
        player.drawTo(window);
        window.display();
    }

    return 0;
}

Game::Game()
{
	window.setSize(sf::Vector2u(width, height));
	window.setTitle("Platformer");
}
