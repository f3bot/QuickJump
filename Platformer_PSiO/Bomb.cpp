#include <iostream>
#include "Bomb.h"


Bomb::Bomb() : sf::Sprite()
{
    if (!bombTexture.loadFromFile("assets/Explosions/bomb_fine.png")) {
        std::cerr << "Bomb texture failed to load\n";
    }

    if (!explosionTexture.loadFromFile("assets/Explosions/Explosion.png")) {
        std::cerr << "Explosion texture failed to load\n";
    }

    position.x = 500.f;
    position.y = -400.f;

    setTexture(bombTexture);
    setPosition(position);
    setScale({ .15,.15 });

    canMove = true;

    initializeVector();
    animationStateExplosion = 0;
    animationTimeExplosion = 0;

    hasCollided = false;
    hasSetTextureRect = false;
    animationTimeTest = 0;
}

Bomb::~Bomb()
{
    std::cout << "Bomb destroyed\n";
}

bool Bomb::initializeVector()
{

    sf::FloatRect a[8] = { {205,16,68,68}, {303,19,62,63}, {391,11,78,74}, {488,7,77,81}, {579,7,79,76}, {678,6,75,75}, {773,6,79,63},{868,5,81,68} //Tileset coordinates or smth
    };

    explosionVector.insert(
        explosionVector.begin(),
        std::begin(a),
        std::end(a)
    );

    return true;
}

void Bomb::animateExplosion(float dt, Player& player)
{
    setTexture(explosionTexture);

    // top left width height

    animationTimeExplosion += dt;

    if (!hasSetTextureRect) {
        setTextureRect(explosionVector[0]);
        hasSetTextureRect = true;
    }
    else if (animationTimeExplosion >= 100000) {
        animationStateExplosion = (animationStateExplosion + 1) % explosionVector.size();
        setTextureRect(explosionVector[animationStateExplosion]);
        animationTimeExplosion = 0;
        std::cout << animationStateExplosion << std::endl;
    }

    if (animationStateExplosion == 7){
        player.setDead();
    }
}

void Bomb::collisionWithPlayer(Player& player, float dt)
{
    if (player.getGlobalBounds().intersects(getGlobalBounds())) {
        if (player.getShielded()) {
            hasCollided = true;
            animationTimeTest = 0;  
        }
        else {
            std::cout << "Eksplozja\n";
            setScale({ 1.5,1.5 });
            animateExplosion(dt, player);
            player.isGrounded = true;
            player.canMove = false;
            canMove = false;
        }
    }

    if (hasCollided) {
        animationTimeTest += dt;
        std::cout << "added\n" << animationTimeTest << std::endl;
        if (animationTimeTest > 1000000) {
            std::cout << "Shielded\n";
            player.setShielded(false);
            hasCollided = false;
            animationTimeTest = 0;  
        }
    }
}


void Bomb::resetPosition(sf::RenderWindow& window, Player& player)
{
    if (getPosition().y > player.getPosition().y + window.getSize().y + 100) {
        position.x = randomFloat(50, 500);
        position.y = player.getPosition().y - window.getSize().y;
        std::cout << "set\n";
    }
}

void Bomb::fallDown()
{
    if (canMove) {
        position.y += gravitationalForce;
    }
}

void Bomb::moveUp(float speed)
{
    if (canMove) {
        move(0, -1 * speed);
    }
}

float Bomb::randomFloat(float min, float max)
{
    static std::default_random_engine e{ static_cast<long unsigned int>(time(0)) };
    std::uniform_real_distribution<float> d{ min, max };
    return d(e);
}



void Bomb::update(Player& player, sf::RenderWindow& window, float dt)
{
    std::cout << player.getShielded() << std::endl;

    fallDown();
    resetPosition(window, player);
    setPosition(position);
    collisionWithPlayer(player, dt);
    moveUp(player.getVertical());

    window.draw(*this);
}
