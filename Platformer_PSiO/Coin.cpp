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
	randomX = 0;

	randomFloatFound = false;
}

void Coin::changePosition(Platform* platform, Player& player, std::vector<Platform*> platVec)
{
	if (!randomFloatFound) {
		randomX = randomFloat(40, 320);
		randomFloatFound = true;
	}
	setPosition(platform->getPositionX() + randomX, platform->getPositionY() + 10);
	std::cout << platform->getPositionY() + player.getPosition().y << std::endl;

	auto it = std::find(platVec.begin(), platVec.end(), platform);
	if (it == platVec.end()) {
		randomFloatFound = false;
	}
}

void Coin::collideWithPlayer(Player& player)
{
	if (player.getGlobalBounds().intersects(getGlobalBounds())) {
		std::cout << "Kolizja\n";
	}

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

float Coin::randomFloat(float min, float max)
{
	static std::default_random_engine e{ static_cast<long unsigned int>(time(0)) };
	std::uniform_real_distribution<float> d{ min, max };
	return d(e);
}

void Coin::updateCoin(Player& player, sf::RenderWindow& window, float dt, Platform* platform, std::vector<Platform*> platVec)
{
	changePosition(platform, player, platVec);
	animateCoin(dt);
	window.draw(*this);
}
