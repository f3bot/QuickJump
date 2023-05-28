#include "Coin.h"

Coin::Coin(Platform *plat) : sf::Sprite()
{

	handleTexture();

	position.x = plat->getPositionX();
	position.y = plat->getGlobalBoundsTop();

	setTexture(coinTexture);
	setTextureRect(textureVector[0]);
	setScale({ 0.5,0.5 });
	setPosition(position);

	animationTime = 0;
	animationState = 0;
	score = 0;
}

bool Coin::handleTexture()
{
	if (!coinTexture.loadFromFile("assets/01coin.png")) {
		std::cerr << "Failed to load coin texture\n";
	}

	sf::FloatRect a[8] = { {20,16,90, 88}, {144,16,73,88}, {268,16,65,88}, {400,16,41,88}, //Tileset coordinates or smth
	{528,16,25,88}, {640,16,41,88}, {748,16,65,88}, {864,16,73,87}
	};

	textureVector.insert(
		textureVector.begin(),
		std::begin(a),
		std::end(a)
	);

	return true;
}

void Coin::animateCoin(float dt)
{
	animationTime += dt;

	if (animationTime >= 100000) {
		animationState = (animationState + 1) % textureVector.size();
		setTextureRect(textureVector[animationState]);
		animationTime = 0;
	}

}

void Coin::updateCoin(Player& player, sf::RenderWindow& window, float dt, Platform *platform)
{
	setPosition(position);
	animateCoin(dt);
	window.draw(*this);
}
