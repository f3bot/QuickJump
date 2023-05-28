#include "Player.h"
#include "Options.h"

Player::Player(sf::RenderWindow& window) : sf::Sprite()
{
	//Animation and texture stuff


	animationTimeRun = 0;
	animationTimeIdle = 0;


	animationStateRun = 0;
	animationStateIdle = 0;

	std::cout << "Obiekt klasy gracz\n";
	if (!playerTexture.loadFromFile("assets/Jungle Asset Pack/Character/sprites/idle.gif")) {
		std::cerr << "Nie wczytano tekstury gracza\n";
	}

	jumpingTexture = sf::Texture();
	breathingTexture = sf::Texture();
	runningTexture = sf::Texture();

	handleBreathing();
	handleJumping();
	handleRunning();
	setTexture(breathingTexture);
	setTextureRect(BreathingTextureVector[0]);
	position.x = 200.f;
	position.y = 300.f;
	setPosition(200.f, -10.f);
	setScale({ 2.5,2.5 });

	//Movement

	isGrounded = false;
	verticalSpeed = 0;
	horizontalSpeed = 0;
	isJumping = false;
	isDead = false;
	left = false;
	right = false;
	canMove = true;

	//


	//Bounds Drawing

	bounds.setSize(sf::Vector2f(getGlobalBounds().width, getGlobalBounds().height));
	bounds.setPosition(getPosition());
	bounds.setOutlineThickness(2.f);
	bounds.setOutlineColor(sf::Color::Red);
	bounds.setFillColor(sf::Color::Transparent);
}

void Player::movementJump()
{
	if (isGrounded) { //If isGrounded stop movement
		verticalSpeed = 0;
		isJumping = false;
	}
	else if(!isGrounded) {
		verticalSpeed += gravitationalForce;
		position.y += verticalSpeed;


		move(0, verticalSpeed);
	}

	if (verticalSpeed >= 5.f) {
		verticalSpeed = 5.f;
	}
}

void Player::movementHorizontal()
{
	horizontalSpeed = 0;

	if (left && canMove) {
		setScale({ -2.5, 2.5 });
		horizontalSpeed = -2.5f;
		position.x += horizontalSpeed;
		setOrigin(getLocalBounds().width, 0);
	}
	if (right && canMove) {
		horizontalSpeed = 2.5f;
		position.x += horizontalSpeed;
		setScale({ 2.5, 2.5 });
		setOrigin(0, 0);
	}

}



void Player::handleEvents(sf::Event& e)
{
	if (e.type == sf::Event::KeyPressed) {
		if (e.key.code == sf::Keyboard::Up && !isJumping && canMove) {
			verticalSpeed = -4.25f;
			isJumping = true;
			isGrounded = false;
		}
		if (e.key.code == sf::Keyboard::X) {
			std::cout << getPosition().x << " " << getPosition().y << std::endl;
		}
		if (e.key.code == sf::Keyboard::LAlt) { // Testing -  will remove later
			setPosition(200, 300);
		}
		if (e.key.code == sf::Keyboard::Z) {
			isGrounded = true;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		left = true;
		right = false;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		left = false;
		right = true;
	}
	else {
		left = false;
		right = false;
	}
}


void Player::drawTo(sf::RenderWindow& window)
{
	setPosition(position.x, position.y);
	bounds.setPosition(getPosition());
	window.draw(*this);
	window.draw(bounds);
	isGrounded = false;
}

void Player::borderCollision(sf::RenderWindow& window)
{
	if (getGlobalBounds().top + getGlobalBounds().height >= window.getSize().y) {
		isGrounded = true;
		isJumping = false;
	}
}

double Player::getVertical()
{
	return verticalSpeed;
}

double Player::setVertical(double s)
{
	verticalSpeed = s;
	return verticalSpeed;
}

double Player::getHorizontal()
{
	return horizontalSpeed;
}

bool Player::getJumping()
{
	if (isJumping) {
		return true;
	}

	return false;
}

bool Player::getDead()
{
	return isDead;
}

void Player::setDead()
{
	isDead = true;
}

void Player::updateAll(float dt, sf::RenderWindow& window, sf::Event& e)
{
	movementHorizontal();
	movementJump();
	window.draw(*this);
	handleTextureChange(dt);
}

bool Player::handleBreathing()
{

	if (!breathingTexture.loadFromFile("assets/Jungle Asset Pack/Character/sprites/tileSetBreathing.png")) {
		std::cerr << "Nie wczytano tekstury gracza *tileset breathing\n";
		return false;
	}

	sf::FloatRect a[12] = { {0,1,19,33}, {19,1,19,33}, {38,1,19,33}, {57,1,19,33}, //Tileset coordinates or smth
		{76,1,19,33}, {95,1,19,33}, {114,1,19,33}, {133,1,19,33}
		, {152,1,19,33}, {171,1,19,33}, {190,1,19,33}, {209,1,19,33}
	};

	BreathingTextureVector.insert(
		BreathingTextureVector.begin(),
		std::begin(a),
		std::end(a)
	);

	return true;
}

void Player::setBreathing(float dt)
{
	setTexture(breathingTexture);
	
	//top left width height

	animationTimeIdle += dt;

	if (animationTimeIdle >= 100000) {
		animationStateIdle = (animationStateIdle + 1) % BreathingTextureVector.size();
		setTextureRect(BreathingTextureVector[animationStateIdle]);
		animationTimeIdle = 0;
	}
}

bool Player::handleJumping()
{
	if (!landingTexture.loadFromFile("assets/Jungle Asset Pack/Character/sprites/landing.png")) {
		std::cerr << "Nie wczytano landing\n";
		return false;
	}

	if (!jumpingTexture.loadFromFile("assets/Jungle Asset Pack/Character/sprites/jump.png")) {
		std::cerr << "Nie wczytano tekstury gracza *tileset jumping\n";
		return false;
	}

	return true;
}

void Player::setJumping()
{
	if (verticalSpeed > 0) {
		setTexture(landingTexture);
		setTextureRect(sf::IntRect(0, 0, 17, 34));
	}
	else if (verticalSpeed < 0) {
		setTexture(jumpingTexture);
		setTextureRect(sf::IntRect(0, 0, 17, 34));
	}
}

bool Player::handleRunning()
{
	if (!runningTexture.loadFromFile("assets/Jungle Asset Pack/Character/sprites/tileSetRunning.png")) {
		std::cerr << "Nie wczytano tekstury gracza *tileset Running\n";
		return false;
	}



	sf::FloatRect a[8] = { {0,1,21,33}, {22,2,18,31}, {45,2,15,31}, {65,0, 18,30}, //Tileset coordinates or smth
		{86,0,18,33}, {106,2,17,31}, {127,2,17,31}, {147,0, 21,29}
	};

	RunningTextureVector.insert(
		RunningTextureVector.begin(),
		std::begin(a),
		std::end(a)
	);

	return true;
}

void Player::setRunning(float dt)
{
	setTexture(runningTexture);

	animationTimeRun += dt;

	if (animationTimeRun >= 100000) {
		animationStateRun = (animationStateRun + 1) % RunningTextureVector.size();
		setTextureRect(RunningTextureVector[animationStateRun]);
		animationTimeRun = 0;
	}
}

void Player::handleTextureChange(float dt)
{
	if (left && canMove || right && canMove) {
		setRunning(dt);
	}

	if (isJumping && canMove) {
		setJumping();
	}


}

