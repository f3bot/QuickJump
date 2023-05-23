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
    for (auto a : platformVec) {
        if (a->getPositionY() > player.getPosition().y + height + 100) { // + 300, because we want the platform to slightly come back if the player falls down
            for (auto it = platformVec.begin(); it != platformVec.end(); ) { // Then, we will delete the player and end the game at height + 301 or smth
                delete* it;
                it = platformVec.erase(it);
                std::cout << a->getPositionY() << std::endl;
                return true;
            }
        }
    }

    return false;
}

void Game::initializeGameWithPlatforms()
{
    platformVec = {
        {new Platform(200.f, 300.f)},
        {new Platform(200.f, 100.f)},
        {new Platform(200.f, -300.f)},
        {new Platform(200.f, -400.f)},
        {new Platform(200.f, -500.f)},
        {new Platform(200.f, -600.f)},
        {new Platform(200.f, -700.f)},
        {new Platform(200.f, -800.f)},
        {new Platform(200.f, -900.f)},
        {new Platform(200.f, -1000.f)}
    };
}

int Game::run()
{
    sf::Clock clock;
    sf::View view = window.getDefaultView();

    Background background_texture(window);
    Player player;

    initializeGameWithPlatforms();

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
        
        background_texture.updatePosition(window, view);

        clock.restart();
        player.movementHorizontal(clock.getElapsedTime().asMicroseconds());
        player.handleTextureChange(clock.getElapsedTime().asMicroseconds());
        player.borderCollision(window);

        for (auto& a : platformVec) {
            movePlatforms(player);
            a->playerBlockCollision(player);
            a->drawTo(window);
        }

        background_texture.drawBackground(window);

        handleWorldGeneration(player);

        player.movementJump();

        view.setCenter(player.getPosition());
        window.setView(view);

        player.drawTo(window);

        background_texture.setPosition(player.getPosition());

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
