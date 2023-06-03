#include "Game.h"
#include "Background.h"
#include "Player.h"
#include "Platform.h"
#include "Bomb.h"
#include "Coin.h"
#include "MainMenu.h"
#include "AnimatedGIF.h"
#include "Spikes.h"
#include <iostream>
void Game::initVariables()
{

}


void Game::movePlatforms(Player& player)
{
    for (auto &a : platformVec) {
        a->moveUp(0.2 * player.getVertical()); // Platforms will move in the opposite direction as the player, this will give the 
    }                                           //Illusion that the world is smoothly generated, rather than platforms just appearing out of nowhere

}//NOT USED RN

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
        if ((*it)->getPositionY() > player.getPosition().y + height - 100 || (*it)->getAnimationState() == 8)
        {
            delete* it;
            it = platformVec.erase(it);
            platformsDeleted = true;
            std::cout << "Usunieta platforme " << it._Ptr << std::endl;
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
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    sf::Clock clock;
    sf::View view = window.getDefaultView();
    Bomb bomb;

    sf::Sprite gifSprite;

    Background background_texture(window);
    Player player(window);

    initializeGameWithPlatforms();

    sf::RenderWindow window(sf::VideoMode(width, height), "Platformer!");

    window.setFramerateLimit(144);

    Coin* coin;
    coin = new Coin(player, platformVec[2]);

    Spikes spikes;

    MainMenu* mainMenu;

    mainMenu = new MainMenu(width, height);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            player.handleEvents(event);
            mainMenu->processEvents(event, player, background_texture, platformVec);
        }

        window.clear(sf::Color::Black);

        if (!mainMenu->getState()) {
            mainMenu->drawTo(window);
            mainMenu->deleteListener();
            window.draw(gifSprite);
        }
        else {
            if (!player.getDead()) {
                background_texture.drawBackground(window);

                for (auto& a : platformVec) {
                    a->playerBlockCollision(player);
                    a->setDestruction(clock.getElapsedTime().asMicroseconds());
                    a->drawTo(window);
                }


                handleWorldGeneration(player);

                player.movementHorizontal(background_texture);
                player.movementJump(background_texture);
                //background_texture.move(player.getHorizontal(), player.getVertical());

                view.setCenter(player.getPosition());
                window.setView(view);

                player.drawTo(window, background_texture);
                player.handleTextureChange(clock.getElapsedTime().asMicroseconds());

               // spikes.update(window, player);
               bomb.update(player, window, clock.getElapsedTime().asMicroseconds());
               coin->updateCoin(player, window, clock.getElapsedTime().asMicroseconds(), platformVec[2], platformVec);


                clock.restart();

                
                //Exit menu, Play again, power up(shield bomba, 5 monet, wyzszy skok), hall of fame(tierlist)

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
}
