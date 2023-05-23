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
    for (auto a : platformVec) {
        a->moveUp(0.35 * player.getVertical()); // Platforms will move in the opposite direction as the player, this will give the 
    }                                           //Illusion that the world is smoothly generated, rather than platforms just appearing out of nowhere
}

void Game::handleWorldGeneration()
{
    //First portion of this 
    deleteOutOfBoundsPlatforms();


}

void Game::deleteOutOfBoundsPlatforms()
{
    for (auto a : platformVec) {
        std::cout << a->getPositionY() << std::endl;
        if (a->getPositionY() > height + 300) { // + 300, because we want the platform to slightly come back if the player falls down
            for (auto it = platformVec.begin(); it != platformVec.end(); ) { // Then, we will delete the player and end the game at height + 301 or smth
                delete* it;
                it = platformVec.erase(it);
            }
        }
    }
}

int Game::run()
{
    sf::Clock clock;

    Background background_texture;
    Player player;
    Platform* plat3 = new Platform(400.f, 300.f);
    Platform* plat = new Platform(200.f, 500.f);
    Platform* plat2 = new Platform( 200.f, 700.f);

    platformVec.push_back(plat);
    platformVec.push_back(plat2);
    platformVec.push_back(plat3);

    std::cout << "Number of platforms: " << platformVec.size() << std::endl;

    sf::RenderWindow window(sf::VideoMode(width, height), "Platformer!");

    //

    std::cout << "Number of platforms: " << platformVec.size() << std::endl;

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
        
        clock.restart();
        player.movementHorizontal(clock.getElapsedTime().asMicroseconds());
        player.handleTextureChange(clock.getElapsedTime().asMicroseconds());
        player.borderCollision(window);

        player.isGrounded = false;

        for (auto& a : platformVec) {
            movePlatforms(player);
            a->playerBlockCollision(player);
            a->drawTo(window);
        }

        handleWorldGeneration();

        player.movementJump();


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
