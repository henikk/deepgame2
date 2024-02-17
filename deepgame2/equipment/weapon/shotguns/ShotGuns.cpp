#include "ShotGuns.h"

ShotGuns::ShotGuns(std::string _pathToTexture, std::string _pathToBulletTexture, std::string _pathToShellTexture, std::vector<std::string> _pathsToSounds)
	: Weapon(_pathToTexture, _pathToBulletTexture, _pathToShellTexture, _pathsToSounds)
{
	this->m_damage = 4;
	this->m_maxAccuracy = 75;
	this->m_bulletsPerShot = 5;
	this->m_accuracyRecoverySpeed = 25.0f;
	this->m_recoil = 15.0f;
	this->m_bulletSpeed = 3200;
	this->m_fireRange = 2000;
	this->m_viewRange = 1600; // TEMP
	this->m_capacity = 6;
	this->m_ammo = 18;
	this->m_magazine = this->m_capacity;
	this->m_reloadTime = 3.5f;
	this->m_fireRate = 1.25f;

	this->m_singleShot = true;
	this->m_showSmoke = true;
	this->m_showFlash = true;
	this->m_showShells = true;
	this->m_dynamicAccuracy = true;

	this->m_shotFrameCount = 14;
	this->m_emptyFrameCount = 6;
	this->m_reloadFrameCount = 14;
	this->m_frame = sf::IntRect(0, 0, 160, 32);

	this->m_gunOffset = sf::Vector2f(0.0f, 25.0f);
	this->m_barrelOffset = sf::Vector2f(98.0f, 1.0f);
	this->m_ejectionPortOffset = { 43.0f, 0.0f };

	this->m_shellColor = sf::Color::White;
	this->m_shellTexture.loadFromFile(this->m_pathToShellTexture);
	this->m_shellInitialScale = { 1.0f, 1.0f };
	this->m_shellMaxScale = { 1.0f, 1.0f };
	this->m_shellInitialAlpha = 255;
	this->m_shellRotationSpeed = 1500;
	this->m_shellSpeed = 200;
	this->m_shellDownwardForce = 250.0f;
	this->m_shellAcceleration = 2.0f;
	this->m_shellLifeTime = 2.0f;

	this->m_particleColor = sf::Color::White;
	this->m_particleInitialScale = { 0.1f, 0.1f };
	this->m_particleMaxScale = { 0.14f, 0.14f };
	this->m_particleRotationSpeed = 55;
	this->m_particleInitialAlpha = 25;
	this->m_particleSpeed = 150;
	this->m_particleAcceleration = 1.2f;
	this->m_particleUpwardForce = 30.0f;
	this->m_particleLifeTime = 0.15f;

	// Move this to Weapon.cpp
	this->m_texture.loadFromFile(_pathToTexture);
	this->m_bulletTexture.loadFromFile(_pathToBulletTexture);
	this->m_body.setTexture(&this->m_texture);
	this->m_body.setTextureRect(this->m_frame);
	this->m_body.setFillColor(sf::Color::White);
	this->m_body.setSize(sf::Vector2f(this->m_frame.width, this->m_frame.height));
	this->m_body.setOrigin(0.0f, (this->m_body.getSize().y / 2.0f - this->m_barrelOffset.y));
}

ShotGuns::~ShotGuns()
{}

void ShotGuns::Shoot()
{
	Weapon::Shoot();
}

void ShotGuns::Reload()
{
	Weapon::Reload();
}

void ShotGuns::AngleControl(const sf::RenderWindow* target)
{
	Weapon::AngleControl(target);
}

void ShotGuns::update(const sf::RenderWindow* target, float deltaTime)
{
	Weapon::update(target, deltaTime);
}

void ShotGuns::updateInput(const sf::RenderWindow* target)
{
	Weapon::updateInput(target);
}

void ShotGuns::updateTime()
{
	Weapon::updateTime();
}

void ShotGuns::render(sf::RenderWindow* target)
{
	Weapon::render(target);
}
