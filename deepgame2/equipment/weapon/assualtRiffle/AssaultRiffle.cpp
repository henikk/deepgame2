#include "AssaultRiffle.h"

AssaultRiffle::AssaultRiffle(std::string _pathToTexture, std::string _pathToBulletTexture, std::string _pathToParticleTexture, std::vector<std::string> _pathsToSounds)
	: Weapon(_pathToTexture, _pathToBulletTexture, _pathToParticleTexture, _pathsToSounds)
{
	this->m_damage = 15;
	this->m_maxAccuracy = 99;
	this->m_bulletsPerShot = 1;
	this->m_accuracyRecoverySpeed = 42.0f;
	this->m_recoil = 6.8f;
	this->m_bulletSpeed = 10000;
	this->m_fireRange = 2000;
	this->m_capacity = 30;
	this->m_ammo = 90;
	this->m_magazine = this->m_capacity;
	this->m_reloadTime = 4.0f;
	this->m_fireRate = 12.5f;

	this->m_singleShot = false;
	this->m_showSmoke = true;
	this->m_showFlash = true;
	this->m_dynamicAccuracy = true;

	this->m_shotFrameCount = 10;
	this->m_emptyFrameCount = 8;
	this->m_reloadFrameCount = 10;
	this->m_frame = sf::IntRect(0, 0, 128, 48);

	this->m_barrelOffset = sf::Vector2f(86.0f, 7.0f);
	this->m_gunOffset = sf::Vector2f(0.0f, 35.0f);

	this->m_particleColor = sf::Color::White;
	this->m_particleSmokeTexture.loadFromFile(this->m_pathToParticleTexture);
	this->m_particleInitialScale = { 0.06f, 0.06f };
	this->m_particleMaxScale = {0.1f, 0.1f};
	this->m_particleRotationSpeed = 55;
	this->m_particleInitialAlpha = 100;
	this->m_particleSpeed = 50;
	this->m_particleAcceleration = 1.0f;
	this->m_particleUpwardForce = 1.0f;
	this->m_particleLifeTime = 0.3f;

	// Move this to Weapon.cpp
	this->m_texture.loadFromFile(_pathToTexture);
	this->m_bulletTexture.loadFromFile(_pathToBulletTexture);
	this->m_body.setTexture(&this->m_texture);
	this->m_body.setTextureRect(this->m_frame);
	this->m_body.setFillColor(sf::Color::White);
	this->m_body.setSize(sf::Vector2f(this->m_frame.width, this->m_frame.height));
	this->m_body.setOrigin(0.0f, (this->m_body.getSize().y / 2.0f - this->m_barrelOffset.y));
}

AssaultRiffle::~AssaultRiffle()
{}

void AssaultRiffle::Shoot()
{
	Weapon::Shoot();
}

void AssaultRiffle::Reload()
{
	Weapon::Reload();
}

void AssaultRiffle::AngleControl(const sf::RenderWindow* target)
{
	Weapon::AngleControl(target);
}

void AssaultRiffle::update(const sf::RenderWindow* target, float deltaTime)
{
	Weapon::update(target, deltaTime);
}

void AssaultRiffle::updateInput(const sf::RenderWindow* target)
{
	Weapon::updateInput(target);
}

void AssaultRiffle::updateTime()
{
	Weapon::updateTime();
}

void AssaultRiffle::render(sf::RenderWindow* target)
{
	Weapon::render(target);
}
