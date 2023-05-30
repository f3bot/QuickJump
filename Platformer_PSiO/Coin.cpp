#include "Coin.h"
#include "Player.h"

Coin::Coin(Player& player, Platform* plat) : sf::Sprite()
{

	handleTexture();

	if (!font.loadFromFile("fonts/font3.ttf")) {
		std::cerr << "Nie wczytano fonta\n";
	}


	position.x = plat->getPositionX();
	position.y = plat->getPositionY() - 40;

	platformIndex = 0;

	setTexture(coinTexture);
	setTextureRect(textureVector[0]);
	setScale({ 0.5,0.5 });
	setPosition(position);

	score = 0;


	scoreText.setFont(font);
	scoreText.setString(std::to_string(score));
	scoreText.setCharacterSize(80);

	coinSprite.setTexture(coinTexture);
	coinSprite.setTextureRect(textureVector[0]);
	coinSprite.setScale({ 0.75, 0.75 });


	animationTime = 0;
	animationState = 0;
	randomX = 0;
	r = 0;

	isDeleted = false;

	randomIntFound = false;
}

bool Coin::checkDeleted(std::vector<Platform*> platVec, Platform* plat)
{
	if (getPosition().y > platVec[0]->getPositionY()) {
		return true;
	}


	return false;
}


void Coin::changePosition(Platform* platform, Player& player, std::vector<Platform*> platVec)
{
	if (!randomIntFound) {
		r = 2 + randomInt(3);
		randomIntFound = true;
		checkDeleted(platVec, platVec[r]);
	}

	if (player.getGlobalBounds().intersects(getGlobalBounds()) || checkDeleted(platVec, platVec[r])) {
		platformIndex = r;
		position.x = platVec[platformIndex]->getPositionX() + randomFloat(30, 160);
		position.y = platVec[platformIndex]->getPositionY() - 40;
		randomIntFound = false;
		checkDeleted(platVec, platVec[r]);

		if (player.getGlobalBounds().intersects(getGlobalBounds())) {
			score++;
		}
	}
	

	setPosition(position);
}



bool Coin::collideWithPlayer(Player& player)
{
	if (player.getGlobalBounds().intersects(getGlobalBounds())) {
		score++;
		return true;
	}
	
	return false;

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

int Coin::randomInt(int max)
{
	return rand() % max;
}



float Coin::randomFloat(float min, float max)
{
	static std::default_random_engine e{ static_cast<long unsigned int>(time(0)) };
	std::uniform_real_distribution<float> d{ min, max };
	return d(e);
}

void Coin::updateCoin(Player& player, sf::RenderWindow& window, float dt, Platform* platform, std::vector<Platform*> platVec)
{
	coinSprite.setPosition(player.getPosition().x + 385, player.getPosition().y - 480);
	scoreText.setPosition(player.getPosition().x + 270, player.getPosition().y - 500);
	scoreText.setString(std::to_string(score));
	animateCoin(dt);


	changePosition(platform, player, platVec);
	window.draw(*this);
	window.draw(coinSprite);
	window.draw(scoreText);
}
