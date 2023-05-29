#include "Platform.h"

Platform::Platform(float xPos, float yPos)
{
	size.x = 350;
	size.y = 35;
	rect.setSize(size);
	rect.setPosition(xPos, yPos);

	handleTexture();

	isStanding = false;
	isDestroyed = false;

	animationTime = 0;
	animationState = 0;
	selected = 0;


	std::cout << "Utworzono platforme\n";
	std::cout << rect.getPosition().x << "  " << rect.getGlobalBounds().top << std::endl;

}

Platform::~Platform()
{
	std::cout << "Usunieto platforme\n";
}

bool Platform::handleTexture()
{
	if (selected == 0) {
		if (!t.loadFromFile("assets/Platform_x.png")) {
			std::cerr << "Nie wczytano tekstury platformy\n";
		}
	}
	else {
		if (!t.loadFromFile("assets/Platform_x_2.png")) {
			std::cerr << "Nie wczytano tekstury platformy\n";
		}
	}

	t.setRepeated(true);
	rect.setTexture(&t);

	//Populating the vector

	sf::FloatRect a[9] = { {1,1,96, 16}, {1,18,96,16 }, {1,35,96,16}, {1,52, 96, 16}, //Tileset coordinates or smth
	{1,69,96,16}, {1,86,96,16}, {1,103,96,16}, {1, 120, 96, 16}, {1,137,96,16}
	};

	textureVector.insert(
		textureVector.begin(),
		std::begin(a),
		std::end(a)
	);

	rect.setTextureRect(textureVector[0]);

	return true;
}

void Platform::drawTo(sf::RenderWindow& window)
{
	isStanding = false;
	window.draw(rect);
}

void Platform::playerBlockCollision(Player& player)
{

	float leftPlat =  rect.getGlobalBounds().left;
	float topPlat =  rect.getGlobalBounds().top;
	float rightPlat =  rect.getGlobalBounds().left +  rect.getGlobalBounds().width;
	float bottomPlat =  rect.getGlobalBounds().top +  rect.getGlobalBounds().height;

	float leftPlayer = player.getGlobalBounds().left;
	float topPlayer = player.getGlobalBounds().top;
	float rightPlayer = player.getGlobalBounds().left + player.getGlobalBounds().width;
	float bottomPlayer = player.getGlobalBounds().top + player.getGlobalBounds().height;

	if (bottomPlayer >= topPlat && bottomPlayer <= bottomPlat && leftPlayer >= leftPlat && rightPlayer <= rightPlat) {
		if (player.getVertical() >= 0) {
			player.isGrounded = true;
			isStanding = true;
		}
	}
}

Platform::Platform()
{
	std::cout << "Defualt Constructor\n";
}

float Platform::getPositionY()
{

	return rect.getPosition().y;
}

float Platform::getPositionX()
{
	return rect.getPosition().x;
}

float Platform::getGlobalBoundsTop()
{
	return rect.getGlobalBounds().top;
}

int Platform::setSelected(int s)
{
	selected = s;
	return selected;
}

void Platform::setTextures()
{
	rect.setTexture(&t);
}

void Platform::moveUp(float verticalSpeed)
{
	 rect.move(0, -1 * verticalSpeed);
}

int Platform::getAnimationState()
{
	return animationState;
}


void Platform::setDestruction(float dt)
{
	if (isStanding) {
		animationTime += dt;

		if (animationTime >= 250000) {
			animationState = (animationState + 1) % textureVector.size();
			rect.setTextureRect(textureVector[animationState]);
			animationTime = 0;
		}
	}

}
