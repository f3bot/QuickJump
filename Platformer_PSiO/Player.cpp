#include "Player.h"
#include "Options.h"
#include "Background.h"

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
	barrierCreated = false;

	jumpingCounter = 0;
	//


	//Bounds Drawing

	bounds.setSize(sf::Vector2f(getGlobalBounds().width, getGlobalBounds().height));
	bounds.setPosition(getPosition());
	bounds.setOutlineThickness(2.f);
	bounds.setOutlineColor(sf::Color::Red);
	bounds.setFillColor(sf::Color::Transparent);

	selectedTexture = 0;

	//Powerup dependant bools

	isPowerJumped = false;
	isShielded = false;
}

void Player::movementJump(Background& background)
{
	if (isGrounded) { //If isGrounded stop movement
		verticalSpeed = 0;
		isJumping = false;
	}
	else if(!isGrounded) {
		verticalSpeed += gravitationalForce;
		position.y += verticalSpeed;


		move(0, verticalSpeed);
		background.move(0, verticalSpeed);
	}

	if (verticalSpeed >= 5.f) {
		verticalSpeed = 5.f;
	}
}

void Player::movementHorizontal(Background& background)
{

	if (left && canMove) {
		horizontalSpeed = -2.5f;
		background.move(horizontalSpeed, 0);
		position.x += horizontalSpeed;
		setScale({ -2.5, 2.5 });
		setOrigin(getLocalBounds().width, 0);
	}
	if (right && canMove) {
		horizontalSpeed = 2.5f;
		background.move(horizontalSpeed, 0);
		position.x += horizontalSpeed;
		setScale({ 2.5, 2.5 });
		setOrigin(0, 0);
	}

}



void Player::handleEvents(sf::Event& e)
{
	if (e.type == sf::Event::KeyPressed) {
		if (e.key.code == sf::Keyboard::Up && !isJumping && canMove) {
			if (isPowerJumped && jumpingCounter > 0) {
				verticalSpeed = -18.f;
				jumpingCounter--;
			}
			else {
				verticalSpeed = -10.f;
			}
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


void Player::drawTo(sf::RenderWindow& window, Background& background)
{
	setPosition(position.x, position.y);
	bounds.setPosition(getPosition());
	window.draw(*this);
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

int Player::setSelectedTexture(int s)
{
	std::cout << selectedTexture << std::endl;	
	selectedTexture = s;
	std::cout << selectedTexture << std::endl;
	return selectedTexture;
}

void Player::setTextures()
{
	handleJumping();
	handleRunning();
}

bool Player::getJumping()
{
	if (isJumping) {
		return true;
	}

	return false;
}

bool Player::getPowerJump()
{
	return isPowerJumped;
}

bool Player::getShielded()
{
	return isShielded;
}

void Player::setPowerJumped(bool s)
{
	isPowerJumped = s;
}

void Player::setShielded(bool s)
{
	isShielded = s;
}

void Player::setCounter()
{
	jumpingCounter = 3;
}

bool Player::getDead()
{
	return isDead;
}

void Player::setDead()
{
	isDead = true;
}

void Player::updateAll(float dt, sf::RenderWindow& window, sf::Event& e, Background& background)
{
	movementHorizontal(background);
	movementJump(background);
	window.draw(*this);
	handleTextureChange(dt);
}

void Player::updateShield(sf::RenderWindow& window)
{

	if (!barrierCreated && isShielded) {
		barrier = new playerBarrier(*this);
		barrierCreated = true;
	}

	if (isShielded) {
		barrier->drawTo(*this, window);
	}
	else {
		if (barrier != nullptr) {
			delete barrier;
			barrier = nullptr;
			barrierCreated = false;
		}
	}
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
	if (selectedTexture == 0) {
		if (!landingTexture.loadFromFile("assets/Jungle Asset Pack/Character/sprites/landing.png")) {
			std::cerr << "Nie wczytano landing\n";
			return false;
		}

		if (!jumpingTexture.loadFromFile("assets/Jungle Asset Pack/Character/sprites/jump.png")) {
			std::cerr << "Nie wczytano tekstury gracza *tileset jumping\n";
			return false;
		}
		setTextureRect(sf::IntRect(0, 0, 17, 34));
		std::cout << "Debug c - jumping\n";
	}
	else {
		if (!landingTexture.loadFromFile("assets/Medieval Warrior Pack 2/Sprites/Fall.png")) {
			std::cerr << "Nie wczytano landing\n";
			return false;
		}

		if (!jumpingTexture.loadFromFile("assets/Medieval Warrior Pack 2/Sprites/Jump.png")) {
			std::cerr << "Nie wczytano tekstury gracza *tileset jumping\n";
			return false;
		}
		std::cout << "Debug d - landing\n";
	}

	return true;
}

void Player::setJumping()
{
	if (verticalSpeed > 0) {
		setTexture(landingTexture);
		if (selectedTexture == 0) {
			setTextureRect(sf::IntRect(0, 0, 17, 34));
		}
		else {
			setTextureRect(sf::IntRect(60, 59, 31, 36));
		}
	}
	else if (verticalSpeed < 0) {
		setTexture(jumpingTexture);
		if (selectedTexture == 0) {
			setTextureRect(sf::IntRect(0, 0, 17, 34));
		}
		else {
			setTextureRect(sf::IntRect(61, 57, 32, 38));
		}
	}
}

bool Player::handleRunning()
{
	std::cout << "Selected texture = " << selectedTexture << std::endl;

	if (selectedTexture == 0) {
		if (!runningTexture.loadFromFile("assets/Jungle Asset Pack/Character/sprites/tileSetRunning.png")) {
			std::cerr << "Nie wczytano tekstury gracza *tileset Running\n";
			return false;
		}

		std::cout << "Debug a\n";

		sf::IntRect a[8] = {
			{0, 1, 21, 33}, {22, 2, 18, 31}, {45, 2, 15, 31}, {65, 0, 18, 30},
			{86, 0, 18, 33}, {106, 2, 17, 31}, {127, 2, 17, 31}, {147, 0, 21, 29}
		};
		RunningTextureVector.assign(a, a + 8);
	}
	else {
		if (!runningTexture.loadFromFile("assets/Medieval Warrior Pack 2/Sprites/Run.png")) {
			std::cerr << "Nie wczytano tekstury gracza *tileset Running - 2\n";
			return false;
		}

		std::cout << "Debug b\n";

		sf::IntRect a[8] = {
			{60, 58, 26, 37}, {206, 57, 33, 33}, {360, 57, 26, 37}, {514, 58, 18, 37},
			{659, 59, 26, 36}, {806, 57, 34, 29}, {957, 58, 26, 36}, {1113, 59, 20, 36}
		};
		RunningTextureVector.assign(a, a + 8);

		setTextureRect(RunningTextureVector[0]);
	}

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
