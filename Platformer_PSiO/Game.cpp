#include "Game.h"
#include "Background.h"
#include "Player.h"
#include "Platform.h"
#include "MovingPlatform.h"
#include "Bomb.h"
#include "Coin.h"
#include <iostream>
void Game::initVariables()
{

}


void Game::movePlatforms(Player& player)
{
    for (auto &a : platformVec) {
        a->moveUp(0.2 * player.getVertical()); // Platforms will move in the opposite direction as the player, this will give the 
    }                                           //Illusion that the world is smoothly generated, rather than platforms just appearing out of nowhere

}

void Game::handleWorldGeneration(Player& player)
{
    //First portion of this 

    if (deleteOutOfBoundsPlatforms(player)) {
        platformVec.push_back(new Platform(randomCoordinates().x, randomCoordinates().y));
        std::cout << "New platform pushed to vector\n";
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

    for (auto it = platformVec.begin(); it != platformVec.end(); )
    {
        if ((*it)->getPositionY() > player.getPosition().y + height + 100 || (*it)->getAnimationState() == 8)
        {
            delete* it;
            it = platformVec.erase(it);
            platformsDeleted = true;
        }
        else
        {
            ++it;
        }
    }

    return platformsDeleted;
}


void Game::initializeGameWithPlatforms()
{
    platformVec = {
        {new Platform(200.f, 350.f)},
        {new Platform(200.f, 150.f)},
        {new Platform(200.f, -50.f)},
        {new Platform(200.f, -250.f)},
        {new Platform(200.f, -450.f)},
        {new Platform(200.f, -650.f)},
        {new Platform(200.f, -850.f)},
        
    };
}

int Game::run()
{
    sf::Clock clock;
    sf::View view = window.getDefaultView();
    Bomb bomb;

    Background background_texture(window);
    Player player(window);

    initializeGameWithPlatforms();

    sf::RenderWindow window(sf::VideoMode(width, height), "Platformer!");

    window.setFramerateLimit(144);

    Coin coin(platformVec[2]);

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


        if (!player.getDead()) {
            background_texture.drawBackground(window);

            for (auto& a : platformVec) {
                movePlatforms(player);
                a->playerBlockCollision(player);
                a->setDestruction(clock.getElapsedTime().asMicroseconds());
                a->drawTo(window);
            }

            handleWorldGeneration(player);

            player.movementHorizontal();
            player.movementJump();
            background_texture.move(player.getHorizontal(), player.getVertical());

            view.setCenter(player.getPosition());
            window.setView(view);

            player.drawTo(window);
            player.handleTextureChange(clock.getElapsedTime().asMicroseconds());


            bomb.update(player, window, clock.getElapsedTime().asMicroseconds());
            coin.updateCoin(player, window, clock.getElapsedTime().asMicroseconds(), platformVec[1]);


            clock.restart();
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
}
