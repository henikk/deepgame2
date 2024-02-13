#include "Player.h"

Player::Player(sf::Vector2f _size, sf::Color _color, sf::Vector2f _position, u8 _hp, u8 _armor) 
	: Entity(_size, _color, _position), m_hp(_hp), m_armor(_armor)
{
	this->currentPistol = this->pistol; // TEMP
	this->currentAssault = this->assaultRiffle; // TEMP
	this->currentShotgun = this->shotgun;
	this->m_weaponsInInventory = { &this->currentPistol, &this->currentAssault, &this->currentShotgun };
	this->selectedWeapon = WeaponType::TERTIARY;

	this->m_colider = sf::RectangleShape(_size);
	this->m_colider.setFillColor(_color);
	this->m_colider.setPosition(_position);
	this->m_isAlive = true;
	this->m_isGrounded = false;
	this->m_jumpForce = 360.0f;
	this->m_gravity = 9.81f * 150.0f;
	this->m_velocity = {0.0f, 0.0f};
	this->m_speed = 100.0f * 5.0f;
}

Player::~Player(){}

void Player::update(const sf::RenderWindow* target, float deltaTime)
{
	this->updateInput(target, deltaTime);
	this->updateWindowBoundsCollision(target);
	this->updateWeapon(target, deltaTime);
}

void Player::updateWeapon(const sf::RenderWindow* target, float deltaTime)
{
	this->m_weaponPosition = { m_colider.getPosition().x + this->m_colider.getSize().x / 2, this->m_colider.getPosition().y };

	switch (selectedWeapon)
	{
	case WeaponType::PRIMARILY:
		hideAllWeapons();
		this->currentAssault.Select();
		break;

	case WeaponType::SECONDARY:
		hideAllWeapons();
		this->currentPistol.Select();
		break;

	case WeaponType::TERTIARY:
		hideAllWeapons();
		break;

	case WeaponType::QUATERNARY:
		hideAllWeapons();
		this->currentShotgun.Select();
		break;

	default:
		hideAllWeapons();
		break;
	}

	for (auto& weapon : this->m_weaponsInInventory )
	{
		weapon->setPosition(this->m_weaponPosition);
		weapon->update(target, deltaTime);
	}
}

void Player::render(sf::RenderWindow* target)
{ 
	target->draw(this->m_colider); 

	renderWeapon(target);
}

void Player::renderWeapon(sf::RenderWindow* target)
{
	for (auto& weapon : this->m_weaponsInInventory)
		weapon->render(target);
}
// STILL UNFINISHED
void Player::updateInput(const sf::RenderWindow* target, float deltaTime)
{
	//const float groundLevel = target->getSize().y - this->m_colider.getSize().y;

	// Movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->m_velocity.x = -this->m_speed;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->m_velocity.x = this->m_speed;
	else
		this->m_velocity.x = 0.0f;

	// Weapon selecting
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		this->selectedWeapon = WeaponType::PRIMARILY;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		this->selectedWeapon = WeaponType::SECONDARY;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		this->selectedWeapon = WeaponType::TERTIARY;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		this->selectedWeapon = WeaponType::QUATERNARY;


	handleJumpInput(static_cast<float>(target->getSize().y));
	applyGravity(deltaTime);

	this->m_colider.move(this->m_velocity * deltaTime);
}

void Player::handleJumpInput(float targetHeight)
{
	const float playerTop = this->m_colider.getGlobalBounds().top;
	const float playerBottom = playerTop + this->m_colider.getGlobalBounds().height;

	if (playerBottom >= targetHeight)
	{
		this->m_colider.setPosition(this->m_colider.getPosition().x, targetHeight - this->m_colider.getSize().y);
		this->m_velocity.y = 0.0f;
		this->m_isGrounded = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->m_isGrounded)
	{
		if (playerTop <= targetHeight)
		{
			this->jump();
		}
	}
}

void Player::applyGravity(float deltaTime)
{
	if (!this->m_isGrounded)
	{
		/*if (this->m_velocity.y > this->m_gravity)
			this->m_velocity.y = this->m_velocity.y - this->m_gravity;
		else*/
		this->m_velocity.y += this->m_gravity * deltaTime;	
	}
}

void Player::updateWindowBoundsCollision(const sf::RenderWindow* target)
{
	//if (this->m_colider.getGlobalBounds().left <= 0.f)
	//	this->m_colider.setPosition(0.f, this->m_colider.getPosition().y);
	//if (this->m_colider.getGlobalBounds().left + this->m_colider.getGlobalBounds().width >= target->getSize().x)
	//	this->m_colider.setPosition(target->getSize().x - this->getSize().x, this->m_colider.getPosition().y);	
	if (this->m_colider.getGlobalBounds().top <= 0.f)
		this->m_colider.setPosition(this->m_colider.getPosition().x, 0.f);
	if (this->m_colider.getGlobalBounds().top + this->m_colider.getGlobalBounds().height >= target->getSize().y)
		this->m_colider.setPosition(this->m_colider.getPosition().x, target->getSize().y - this->getSize().y);
}

const bool Player::getDirection() const
{
	if (this->m_velocity.x > 0)
		return true;
	else if (this->m_velocity.x < 0)
		return false;
}

const void Player::kill()
{
	this->m_hp = 0;
	this->m_armor = 0;
	this->m_isAlive = false;
}

const void Player::jump()
{
	this->m_velocity.y = -m_jumpForce;
	this->m_isGrounded = false;
}

